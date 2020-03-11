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
    }

    void from_start() {
        double check_time = omp_get_wtime();
        prev_time = check_time;
        std::cout << "Seconds from begin: " << check_time - start_time << std::endl;
    }
} timer;

Camera camera;
std::vector<Object *> objects;
glm::vec3 background_color(0.2, 0.7, 0.8);

std::vector<Light *> lights;

const glm::vec3 *scene_intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &N, Object **object_i) {
    const glm::vec3 *ray_color = nullptr;
    float spheres_dist = std::numeric_limits<float>::max();
    for (auto object : objects) {
        float dist_i;
        const glm::vec3 *col;
        if ((col = object->ray_intersect(ray, dist_i, camera.get_view_matrix())) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            point = ray.get_point(dist_i);
            N = object->get_N(point, camera.get_view_matrix());
            ray_color = col;
            *object_i = object;
        }
    }
    return ray_color;
}

#define MAX_DEPTH 6

glm::vec3 cast_ray(const Ray &ray, size_t depth) {
    glm::vec3 point, N;
    Object *object;
    const glm::vec3 *ray_color = scene_intersect(ray, point, N, &object);

    if (ray_color and depth < MAX_DEPTH) {

        Ray reflect_ray = ray.reflect(N, point);
        glm::vec3 reflect_color = cast_ray(reflect_ray, depth + 1);

        Ray refract_ray = ray.refract(N, object->get_material().refractive_index, point);
        glm::vec3 refract_color = cast_ray(refract_ray, depth + 1);

        float diffuse_light_intensity = 0, specular_light_intensity = 0;
        for (auto l : lights) {
            glm::vec3 light_dir = glm::normalize(l->get_position() - point);
            float light_distance = glm::length(l->get_position() - point);

            Ray shadow_ray(glm::dot(light_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f, light_dir);

            glm::vec3 shadow_pt, shadow_N;
            Object *tmpobj;
            if (scene_intersect(shadow_ray, shadow_pt, shadow_N, &tmpobj) && glm::length(shadow_pt - shadow_ray.orig) < light_distance)
                continue;

            diffuse_light_intensity += l->get_intensity() * std::max(0.f, glm::dot(light_dir, N));

            specular_light_intensity += powf(std::max(0.f, glm::dot(-reflect(-light_dir, N), ray.dir)), object->get_material().specular_exponent) * l->get_intensity();
        }
        Material mat = object->get_material();
        return glm::vec3(*ray_color) * diffuse_light_intensity * mat.albedo[0] +
               glm::vec(*ray_color) * mat.ambient +
               glm::vec3(1, 1, 1) * specular_light_intensity * mat.albedo[1] +
               reflect_color * mat.albedo[2] +
               refract_color * mat.albedo[3];
    }
    return background_color;
}

void ray_caster() {
    std::vector<Ray> rays = camera.generate_rays();
//    int i = 0;
//    int j = 0;
//    timer.start();
//#pragma omp parallel for private(i, j)

    auto lambda = [&rays](int i) {
        for (int j = 0; j < camera.get_width(); j++) {
            glm::vec3 pix = cast_ray(rays[i * camera.get_width() + j], 0);
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
//    timer.check();
}

// понять че как со светом
// Делать ray_tracing

int main() {
    omp_set_num_threads(16);
    IO io("AA", &camera);

    Material glass({0.6, 0.7, 0.8}, {0.0, 0.5, 0.1, 0.8}, 125., 1.5, 0.05f);
    Material ivory({0.4, 0.4, 0.3}, {0.6, 0.3, 0.1, 0.0}, 50., 1.0, 0.2f);
    Material red_rubber({0.3, 0.1, 0.1}, {0.9, 0.1, 0.0, 0.0}, 10., 1.0, 0.2f);
    Material mirror({1.0, 1.0, 1.0}, {0.0, 10.0, 0.8, 0.0}, 1425., 1.0, 0.05);

    objects.push_back(new Sphere(glm::vec3(-3, 0, -16), 2, ivory, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(-1.0, -1.5, -12), 2, glass, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(1.5, -0.5, -18), 3, red_rubber, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(7, 5, -18), 4, mirror, camera.get_view_matrix()));
//    objects.push_back(new Triangle(std::vector({glm::vec3(-3, -3, -18), glm::vec3(3, -3, -20), glm::vec3(0, 3, -18)}), ivory));

//    objects.push_back(new Sphere(glm::vec3(-3, 0, -24), 6, ivory));


    lights.push_back(new Light(glm::vec3(-20, 20, 20), 1.5, camera.get_view_matrix()));
    lights.push_back(new Light(glm::vec3(10, 15, 10), 1, camera.get_view_matrix()));
    lights.push_back(new Light(glm::vec3(0, 0, 0), 0.5, camera.get_view_matrix()));
    lights.push_back(new Light(glm::vec3(10, 15, -30), 0.7, camera.get_view_matrix()));

//    lights.push_back(Light(glm::vec3(0, 0, -35), 0.5));


    ray_caster();
    camera.update_p_frame();


    while (!io.closed()) {
        io.draw(camera.get_frame(), camera.get_width(), camera.get_height());
        if (camera.updated()) {
            for (auto obj : objects) {
                obj->update_position(camera.get_view_matrix());
            }
            for (auto light : lights) {
                light->update_position(camera.get_view_matrix());
            }
            ray_caster();
            camera.update_p_frame();
        }
    }
    return 0;
}
