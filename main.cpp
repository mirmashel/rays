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
#include <Randomizer.h>

#define EPS 1e-3f

Randomizer randomizer{};

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
Background background("../textures/mi.jpg", camera.get_view_matrix());

std::vector<Light_Object *> lights;

static int num_vectors = 0;
std::mutex lock;

const glm::vec3 *scene_intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &N, Object **object_i) {
//    lock.lock();
//    num_vectors++;
//    lock.unlock();
    const glm::vec3 *ray_color = nullptr;
    float objects_dist = std::numeric_limits<float>::max();
    for (auto &object : objects) {
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

float cast_shadow_rays(const Basic_Light &base_light, const glm::vec3 &point, const glm::vec3 &N, const Object *object, const Ray &shadow_ray, float light_distance) {

    glm::vec3 shadow_pt, shadow_N;
    Object *tmpobj;

    float intens = base_light.get_intensity();// * 6;

    if (scene_intersect(shadow_ray, shadow_pt, shadow_N, &tmpobj) && glm::length(shadow_pt - shadow_ray.orig) < light_distance) {
        if (tmpobj->type != LIGHT || tmpobj == object) {

            Ray new_shadow_ray = Ray(glm::dot(shadow_ray.dir, shadow_N) < 0 ? shadow_pt - shadow_N * EPS : shadow_pt +
                                                                                              shadow_N *
                                                                                              EPS,
                             shadow_ray.dir);
            float dist;
            if (tmpobj->ray_intersect(shadow_ray, dist, shadow_pt, shadow_N)) {
                intens *= std::exp(
                        -dist * (1 - tmpobj->get_material().albedo[3])); // понять почему не работает
            }
        }
    }
    return intens;
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
//            std::cout << pp->get_intensity() << std::endl;
            return mat.diffuse_color  * std::exp(-0.3f * dynamic_cast<Light_Object *>(object)->get_intensity());
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

            for (auto &base_light : base_lights) {
                glm::vec3 light_dir = base_light.get_position() - point;
                float light_distance = glm::length(light_dir);
                light_dir /= light_distance;

                Ray shadow_ray(glm::dot(light_dir, N) < 0 ? point - N * EPS : point + N * EPS, light_dir);

                float intens = cast_shadow_rays(base_light, point, N, object, shadow_ray, light_distance);
                // intens /= light_distance;

                diffuse_light_intensity += intens * std::max(0.f, glm::dot(light_dir, N));

                specular_light_intensity += powf(std::max(0.f, glm::dot(reflect(light_dir, N), ray.dir)),
                                                 mat.specular_exponent) *
                                            intens; // Исправить чтоб с Ray было
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

//#define ANTIALIAZING 4

void ray_caster() {
#ifdef  ANTIALIAZING
    std::vector<std::vector<Ray>> rays = camera.generate_few_rays(ANTIALIAZING);
#endif
#ifndef ANTIALIAZING
    std::vector<Ray> rays = camera.generate_rays();
#endif

    num_vectors = rays.size();


    auto lambda = [&rays](int i) {
        for (int j = 0; j < camera.get_width(); j++) {
            glm::vec3 pix(0);
#ifdef ANTIALIAZING
            for (auto r : rays[i * camera.get_width() + j])
                pix += cast_ray(r, 0, 1.f, i);
            pix /= rays[i * camera.get_width() + j].size();
#endif
#ifndef ANTIALIAZING
            pix = cast_ray(rays[i * camera.get_width() + j], 0, 1.f, i);
#endif
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

void ray_pather();

#include <random>

#define PATH  // RAY, PATH

int main() {
#ifdef RAY
    IO io("AA", &camera);
#endif

    Material glass({0.6, 0.7, 0.8}, {0.0, 0.5, 0.1, 0.8}, 125., 2., 0.05f);
    Material ivory({0.4, 0.4, 0.3}, {0.6, 0.3, 0.1, 0.0}, 50., 1.0, 0.2f);
    Material red_rubber({0.3, 0.1, 0.1}, {0.9, 0.1, 0.0, 0.0}, 10., 1.0, 0.2f);
    Material mirror({0.4, 0.4, 0.4}, {0.0, 10.0, 0.8, 0.0}, 1425., 1.0, 0.25);
    Material black_mat = Material({0.4, 0.1, 0.1}, {0.999, 0.5, 0, 0}, 50., 1.5, 0.2f);
    Material green_def = Material({0.1, 0.6, 0.3}, {.999, 0.1, 0.05, 0.0}, 20., 1., 0.2f);


    // Ray tracing scene

//    objects.push_back(new Sphere(glm::vec3(-3, 0, -10), 2, glass, camera.get_view_matrix()));
//    objects.push_back(new Sphere(glm::vec3(2.0, -3, -12), 2, ivory, camera.get_view_matrix()));
//    objects.push_back(new Sphere(glm::vec3(1.5, -0.5, -18), 3, red_rubber, camera.get_view_matrix()));
//    objects.push_back(new Sphere(glm::vec3(7, 5, -18), 4, mirror, camera.get_view_matrix()));
//
//    objects.push_back(new Object_From_File(glm::vec3(3, 0, 6), 1, mirror, camera.get_view_matrix(), "../objects/pyramid.obj"));
//    objects.push_back(new Object_From_File(glm::vec3(-3, 0, -16), 2, ivory, camera.get_view_matrix(),  "../objects/cube.obj"));
//    objects.push_back(new Object_From_File(glm::vec3(-2, 2, -23), 3, red_rubber, camera.get_view_matrix(), "../objects/pyramid.obj"));
//    objects.push_back(new Object_From_File(glm::vec3(3, 0, -6), glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), 2, glass, camera.get_view_matrix(), "../objects/cube.obj"));
//
//    objects.push_back(new Chess_Board(glm::vec3(0, -4, -5), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(5, 5), black_mat, camera.get_view_matrix()));

//    objects.push_back(new Chess_Board(glm::vec3(0, -3, -15), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()), ivory, camera.get_view_matrix()));

//    lights.push_back(new Light_Dot(glm::vec3(-20, 11, 20), 1.5, camera.get_view_matrix()));
//    objects.push_back(new Light_Dot(glm::vec3(-20, 11, 20), 1.5, camera.get_view_matrix()));
//    lights.push_back(new Light_Dot(glm::vec3(10, 10, 10), 1, camera.get_view_matrix()));
//    objects.push_back(new Light_Dot(glm::vec3(10, 10, 10), 1, camera.get_view_matrix()));
//    lights.push_back(new Light_Dot(glm::vec3(0, 0, 0), 1.5, camera.get_view_matrix()));
//    objects.push_back(new Light_Dot(glm::vec3(0, 0, 0), 1.5, camera.get_view_matrix()));
//    lights.push_back(new Light_Dot(glm::vec3(10, -10, -30), 0.7, camera.get_view_matrix()));
//    objects.push_back(new Light_Dot(glm::vec3(10, -10, -30), 0.7, camera.get_view_matrix()));


//    lights.push_back(new Light_Sphere(glm::vec3(-7, 0, 0), 3, 3.f, camera.get_view_matrix()));
//    objects.push_back(new Light_Sphere(glm::vec3(-7, 0, 0), 3, 3, camera.get_view_matrix()));



//    objects.push_back(new Sphere(glm::vec3(2.0, -1.5, -15), 2, red_rubber, camera.get_view_matrix()));
//    objects.push_back(new Sphere(glm::vec3(-1.5, -0.5, -18), 3, ivory, camera.get_view_matrix()));


// Ray path scene
    objects.push_back(new Sphere(glm::vec3(-2, -3, -3), 1., red_rubber, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(-0.2, -2.5, -7), 1.5, ivory, camera.get_view_matrix()));
    objects.push_back(new Sphere(glm::vec3(3., -2.7, -5), 1.3, mirror, camera.get_view_matrix()));

    objects.push_back(new Chess_Board(glm::vec3(0, -4, -5), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(5, 5), black_mat, camera.get_view_matrix()));
    objects.push_back(new Chess_Board(glm::vec3(0, 4, -5), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec2(5, 5), black_mat, camera.get_view_matrix()));
    objects.push_back(new Chess_Board(glm::vec3(0, 0, -10), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec2(5, 4), black_mat, camera.get_view_matrix()));
    objects.push_back(new Chess_Board(glm::vec3(-5, 0, -5), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), glm::vec2(5, 4), green_def, camera.get_view_matrix()));
    objects.push_back(new Chess_Board(glm::vec3(5, 0, -5), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), glm::vec2(5, 4), green_def, camera.get_view_matrix()));

    lights.push_back(new Light_Sphere(glm::vec3(1, -3, -4), 1, 1.5f, camera.get_view_matrix()));
    objects.push_back(new Light_Sphere(glm::vec3(1, -3, -4), 1, 1.5f, camera.get_view_matrix()));

//    lights.push_back(new Light_Dot(glm::vec3(0, 0, 0), 1.5, camera.get_view_matrix()));
//    objects.push_back(new Light_Dot(glm::vec3(0, 0, 0), 1.5, camera.get_view_matrix()));


    timer.start();
#ifdef RAY
    ray_caster();
    camera.update_p_frame();
#endif
#ifdef PATH
    ray_pather();
    camera.update_p_frame();
    camera.save_snapshot();
    std::cout << "rendered" << std::endl;
#endif
    timer.check();


#ifdef RAY
    while (!io.closed()) {
        io.draw(camera.get_frame(), camera.get_width(), camera.get_height());
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
//            ray_pather();
            timer.check();
            camera.update_p_frame();
            timer.check();
        }
    }
#endif

    for (auto obj : objects)
        delete obj;

    for (auto light : lights)
        delete light;

    return 0;
}

#define MAX_PATH_DEPTH 5
#define N_SAMPLES 500


float radiance(const Ray &ray, int depth) {
    if (depth >= MAX_PATH_DEPTH)
        return 0;

    glm::vec3 point, N;
    Object *object;
    const glm::vec3 *ray_color = scene_intersect(ray, point, N, &object);

    if (!ray_color)
        return 0;

    if (object->type == LIGHT) {
        return (dynamic_cast<Light_Object *>(object))->get_intensity() * 100;
    }

    Ray new_ray = ray.new_random_ray(N, point);

    float cos_theta = glm::dot(new_ray.dir, N);

    float BRDF = object->get_material().albedo[0] / M_PI;

    float PDF = (float) 1 / M_PI;

    float intens = radiance(new_ray, depth + 1);

    intens = BRDF / PDF  * cos_theta * intens;
    return  intens;
}

glm::vec3 trace_path(const Ray &ray, int depth, float &intens) {

}

void ray_pather() {
    int num_samples = N_SAMPLES;

#ifdef ANTIALIAZING
    std::vector<std::vector<Ray>> rays = camera.generate_few_rays(ANTIALIAZING);
#endif
#ifndef ANTIALIAZING
    std::vector<Ray> rays = camera.generate_rays();
#endif

    num_vectors = rays.size();


    auto lambda = [&rays, &num_samples](int i) {
        for (int j = 0; j < camera.get_width(); j++) {
            glm::vec3 pix{0.f};
            for (int k = 0; k < num_samples; k++) {
                float tmp_int = 0;
#ifdef ANTIALIAZING
                for (auto r : rays[i * camera.get_width() + j])
                    pix += trace_path(r, 0, tmp_int);
                pix /= rays[i * camera.get_width() + j].size();
#endif
#ifndef ANTIALIAZING
                pix += trace_path(rays[i * camera.get_width() + j], 0, tmp_int);
#endif
            }
            pix /= num_samples;
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