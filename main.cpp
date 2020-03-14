#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "io.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <FrameBuffer.h>
#include <Camera.h>
#include <Objects.h>
#include <omp.h>
#include <Light.h>
#include <thread>
#include <mutex>
#include <background.h>

struct Timer {
private:
    double start_time;
    double prev_time;

public:
    Timer() : start_time{}, prev_time{} {}

    void start() {
        start_time = omp_get_wtime();
        prev_time = start_time;
    }

    void check() {
        double check_time = omp_get_wtime();
        std::cout << "Seconds from prev checkpoint: " << check_time - prev_time << std::endl;
        prev_time = check_time;
    }

    void from_start() {
        double check_time = omp_get_wtime();
        std::cout << "Seconds from begin: " << check_time - start_time << std::endl;
        prev_time = check_time;
    }
} timer;

Camera camera;
std::vector<Object *> objects;
//glm::vec3 background_color(0.2, 0.7, 0.8);
Background background("../textures/ekv.jpg", camera.get_view_matrix());

std::vector<Light_Object *> lights;

static int num_vectors = 0;
std::mutex lock;

const glm::vec3 *scene_intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &N, Object **object_i) {
//    lock.lock();
//    num_vectors++;
//    lock.unlock();
    const glm::vec3 *ray_color = nullptr;
    float objects_dist = std::numeric_limits<float>::max();
    for (auto object : objects) {
        float dist_i;
        const glm::vec3 *col;
        glm::vec3 N1, point1;

        if ((col = object->ray_intersect(ray, dist_i, point1, N1)) && dist_i < objects_dist) {
            objects_dist = dist_i;
            ray_color = col;
            *object_i = object;
            N = N1;
            point = point1;
        }

    }
    return ray_color;
}

#define MAX_DEPTH 10

glm::vec3 cast_ray(const Ray &ray, size_t depth, float contrib, int j) {
    if (contrib < 0.03f) {
        return background.pixel_color(ray);
    }
    glm::vec3 point, N;
    Object *object;
    const glm::vec3 *ray_color = scene_intersect(ray, point, N, &object);

    if (ray_color and depth < MAX_DEPTH) {
        const Material mat = object->get_material();

        if (object->type == LIGHT) {
            return mat.diffuse_color;
        }

        if (contrib < 0.06f) {
            return mat.diffuse_color * mat.ambient;
        }


        Ray reflect_ray = ray.reflect(N, point);
        glm::vec3 reflect_color = cast_ray(reflect_ray, depth + 1, contrib * mat.albedo[2], j);

        Ray refract_ray = ray.refract(N, mat.refractive_index, point);
        glm::vec3 refract_color = cast_ray(refract_ray, depth + 1, contrib * mat.albedo[3], j);

        float diffuse_light_intensity = 0, specular_light_intensity = 0;
        std::vector<Basic_Light> base_lights;
        int pos, col;
        for (auto l : lights) {
            base_lights = l->get_lights(pos, col);

            for (int i = 0; i < base_lights.size(); i++) {
                glm::vec3 light_dir = base_lights[i].get_position() - point;
                float light_distance = glm::length(light_dir);
                light_dir /= light_distance;

                Ray shadow_ray(glm::dot(light_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f, light_dir);
                glm::vec3 shadow_pt, shadow_N;
                Object *tmpobj;
                if (scene_intersect(shadow_ray, shadow_pt, shadow_N, &tmpobj) &&
                    glm::length(shadow_pt - shadow_ray.orig) < light_distance)
                    if (tmpobj->type != LIGHT)
                        continue;

                diffuse_light_intensity += base_lights[i].get_intensity() * std::max(0.f, glm::dot(light_dir, N));

                specular_light_intensity += powf(std::max(0.f, glm::dot(reflect(light_dir, N), ray.dir)),
                                                 mat.specular_exponent) *
                                            base_lights[i].get_intensity(); // Исправить чтоб с Ray было
            }
        }
        return glm::vec3(*ray_color) * diffuse_light_intensity * mat.albedo[0] +
               glm::vec(*ray_color) * mat.ambient +
               glm::vec3(1, 1, 1) * specular_light_intensity * mat.albedo[1] +
               reflect_color * mat.albedo[2] +
               refract_color * mat.albedo[3];
    }
    return background.pixel_color(ray);
}

void ray_caster() {
    std::vector<Ray> rays = camera.generate_rays();

    num_vectors = rays.size();

    auto lambda = [&rays](int i) {
        for (int j = 0; j < camera.get_width(); j++) {
            glm::vec3 pix = cast_ray(rays[i * camera.get_width() + j], 0, 1.f, j);
            float max = std::max(pix[0], std::max(pix[1], pix[2]));
            if (max > 1)
                pix = pix / max;
            camera(i, j) = pix;
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(camera.get_height());
    for (int i = 0; i < camera.get_height(); i++) {
        threads.emplace_back(lambda, i);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Num rays " << num_vectors << std::endl;
}

// понять че как со светом
// Делать ray_tracing

int main() {
//    std::cout << (10 + -1) % 10 << std::endl;

    IO io("AA", &camera);

    Material glass({0.6, 0.7, 0.8}, {0.0, 0.5, 0.1, 0.8}, 125., 2., 0.05f);
    Material ivory({0.4, 0.4, 0.3}, {0.6, 0.3, 0.1, 0.0}, 50., 1.0, 0.2f);
    Material red_rubber({0.3, 0.1, 0.1}, {0.9, 0.1, 0.0, 0.0}, 10., 1.0, 0.2f);
    Material mirror({0.4, 0.4, 0.4}, {0.0, 10.0, 0.8, 0.0}, 1425., 1.0, 0.25);
    Material black_mat = Material({0.4, 0.1, 0.1}, {0.7, 0.5, 0, 0}, 50., 1.5, 0.2f);

    objects.push_back(new Sphere(glm::vec3(-3, 0, -10), 2, glass, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(2.0, -1.5, -12), 2, ivory, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(1.5, -0.5, -18), 3, red_rubber, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(7, 5, -18), 4, mirror, camera.get_view_matrix()));

    objects.push_back(new Object_From_File(glm::vec3(3, 0, 6), 1, mirror, camera.get_view_matrix(), "../objects/pyramid.obj"));
    objects.push_back(new Object_From_File(glm::vec3(-3, 0, -16), 2, ivory, camera.get_view_matrix(),  "../objects/cube.obj"));
    objects.push_back(new Object_From_File(glm::vec3(-2, 2, -23), 3, red_rubber, camera.get_view_matrix(), "../objects/pyramid.obj"));
    objects.push_back(new Object_From_File(glm::vec3(3, 0, -6), glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), 2, glass, camera.get_view_matrix(), "../objects/cube.obj"));

//    objects.push_back(new Cube(glm::vec3(-3, 0, -16), 2, ivory, camera.get_view_matrix()));
//    objects.push_back(new Cube(glm::vec3(-2, 2, -23), 4, red_rubber, camera.get_view_matrix()));
//    objects.push_back(new Cube(glm::vec3(3, 0, -6), 2, glass, camera.get_view_matrix()));

//    objects.push_back(new Chess_Board(glm::vec3(0, -3, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()), ivory, camera.get_view_matrix()));
    objects.push_back(new Chess_Board(glm::vec3(0, -3, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(8, 8), black_mat, camera.get_view_matrix()));
    objects.push_back(new Chess_Board(glm::vec3(0, 13, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec2(8, 8), black_mat, camera.get_view_matrix()));

//    objects.push_back(new Chess_Board(glm::vec3(0, 5, -23), glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec2(16, 16), black_mat, camera.get_view_matrix()));
//    objects.push_back(new Chess_Board(glm::vec3(0, -3, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(15, 15), ivory, camera.get_view_matrix()));
//    objects.push_back(new Chess_Board(glm::vec3(0, -3, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(15, 15), ivory, camera.get_view_matrix()));
//    objects.push_back(new Chess_Board(glm::vec3(0, -3, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(15, 15), ivory, camera.get_view_matrix()));

    lights.push_back(new Light_Dot(glm::vec3(-20, 11, 20), 1.5, camera.get_view_matrix()));
    objects.push_back(new Light_Dot(glm::vec3(-20, 11, 20), 1.5, camera.get_view_matrix()));
    lights.push_back(new Light_Dot(glm::vec3(10, 10, 10), 1, camera.get_view_matrix()));
    objects.push_back(new Light_Dot(glm::vec3(10, 10, 10), 1, camera.get_view_matrix()));
    lights.push_back(new Light_Dot(glm::vec3(0, 0, 0), 0.5, camera.get_view_matrix()));
    objects.push_back(new Light_Dot(glm::vec3(0, 0, 0), 0.5, camera.get_view_matrix()));
    lights.push_back(new Light_Dot(glm::vec3(10, -10, -30), 0.7, camera.get_view_matrix()));
    objects.push_back(new Light_Dot(glm::vec3(10, -10, -30), 0.7, camera.get_view_matrix()));


//    lights.push_back(new Light_Sphere(glm::vec3(0, 7, -25), .7, 3.f, camera.get_view_matrix()));
//    objects.push_back(new Light_Sphere(glm::vec3(0, 7, -25), .7, 3, camera.get_view_matrix()));

//    lights.push_back(Light(glm::vec3(0, 0, -35), 0.5));

    timer.start();
    ray_caster();
    timer.check();

    camera.update_p_frame();

    while (!io.closed()) {
        io.draw(camera.get_frame(), camera.get_aliased_width(), camera.get_aliased_height());
        if (camera.updated()) {
            background.update(camera.get_view_matrix());
            for (auto obj : objects) {
                obj->update_position(camera.get_view_matrix());
            }
            for (auto light : lights) {
                light->update_l_position(camera.get_view_matrix());
            }
            timer.start();
            ray_caster();
            timer.check();
            camera.update_p_frame();
            timer.check();
        }
    }

    for (auto obj : objects)
        delete obj;

    for (auto light : lights)
        delete light;

    return 0;
}
