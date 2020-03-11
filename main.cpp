#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "io.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <FrameBuffer.h>
#include <Camera.h>
#include <Objects.h>
#include <omp.h>

Camera camera;
std::vector<Object *> objects;
glm::vec3 background_color(0.2, 0.7, 0.8);

struct Light {
    Light(const glm::vec3 &p, const float &i) : position(p), intensity(i) {}

    glm::vec3 position;
    float intensity;

    glm::vec3 get_position() {
        glm::vec4 posit = camera.get_view_matrix() * glm::vec4(position, 1);
        return posit;
    }
};

std::vector<Light> lights;

const glm::vec3 *
scene_intersect(const glm::vec3 &orig, const glm::vec3 &dir, glm::vec3 &point, glm::vec3 &N, Object **object_i) {
    const glm::vec3 *ray_color = nullptr;
    float spheres_dist = std::numeric_limits<float>::max();
    for (auto object : objects) {
        float dist_i;
        const glm::vec3 *col;
        if ((col = object->ray_intersect(orig, dir, dist_i, camera.get_view_matrix())) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            point = orig + dir * dist_i;
            N = object->get_N(point, camera.get_view_matrix());
            ray_color = col;
            *object_i = object;
        }
    }
    return ray_color;
}

glm::vec3 reflect(const glm::vec3 &I, const glm::vec3 &N) {
    return I - N * 2.f * glm::dot(I, N);
}

glm::vec3 refract(const glm::vec3 &I, const glm::vec3 &N, const float &refractive_index) { // Snell's law
    float cosi = -std::max(-1.f, std::min(1.f, glm::dot(I, N)));
    float etai = 1, etat = refractive_index;
    glm::vec3 n = N;
    if (cosi < 0) {
        cosi = -cosi;
        std::swap(etai, etat);
        n = -N;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? glm::vec3(0, 0, 0) : I * eta + n * (eta * cosi - sqrtf(k));
}

#define MAX_DEPTH 5

glm::vec3 cast_ray(const glm::vec3 &orig, const glm::vec3 &dir, size_t depth) {
    glm::vec3 point, N;
    Object *object;
    const glm::vec3 *ray_color = scene_intersect(orig, dir, point, N, &object);
    if (ray_color and depth < MAX_DEPTH) {

        glm::vec3 reflect_dir = glm::normalize(reflect(dir, N));
        glm::vec3 reflect_orig = glm::dot(reflect_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f;
        glm::vec3 reflect_color = cast_ray(reflect_orig, reflect_dir, depth + 1);

        glm::vec3 refract_dir = glm::normalize(refract(dir, N, object->get_material().refractive_index));
        glm::vec3 refract_orig = glm::dot(refract_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f;
        glm::vec3 refract_color = cast_ray(refract_orig, refract_dir, depth + 1);

        float diffuse_light_intensity = 0, specular_light_intensity = 0;
        for (auto l : lights) {
            glm::vec3 light_dir = glm::normalize(l.position - point);
            float light_distance = glm::length(l.position - point);

            glm::vec3 shadow_orig = glm::dot(light_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f;
            glm::vec3 shadow_pt, shadow_N;
            Object *tmpobj;
            if (scene_intersect(shadow_orig, light_dir, shadow_pt, shadow_N, &tmpobj) && glm::length(shadow_pt - shadow_orig) < light_distance)
                continue;

            diffuse_light_intensity += l.intensity * std::max(0.f, glm::dot(light_dir, N));
            specular_light_intensity += powf(std::max(0.f, glm::dot(-reflect(-light_dir, N), dir)), object->get_material().specular_exponent) * l.intensity;
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
    std::vector<glm::vec3> rays = camera.generate_rays();
    int i = 0;
    int j = 0;
#pragma omp parallel for private(i, j)
    for (i = 0; i < camera.get_height(); i++) {
        for (j = 0; j < camera.get_width(); j++) {
            camera(i, j) = glm::vec3(0);
            glm::vec3 pix = cast_ray(glm::vec3(0), rays[i * camera.get_width() + j], 0);

            float max = std::max(pix[0], std::max(pix[1], pix[2]));
            if (max > 1)
                pix = pix / max;

            camera(i, j) = pix;
        }
    }
}

// понять че как со светомЫ
// Делать ray_tracing

int main() {
    omp_set_num_threads(16);
    IO io("AA", &camera);

    Material glass({0.6, 0.7, 0.8}, {0.0, 0.5, 0.1, 0.8}, 125., 1.5, 0.05f);
    Material ivory({0.4, 0.4, 0.3}, {0.6, 0.3, 0.1, 0.0}, 50., 1.0, 0.2f);
    Material red_rubber({0.3, 0.1, 0.1}, {0.9, 0.1, 0.0, 0.0}, 10., 1.0, 0.2f);
    Material mirror({1.0, 1.0, 1.0}, {0.0, 10.0, 0.8, 0.0}, 1425., 1.0, 0.05);

    objects.push_back(new Sphere(glm::vec3(-3, 0, -16), 2, ivory));
    objects.push_back(new Sphere(glm::vec3(-1.0, -1.5, -12), 2, glass));
    objects.push_back(new Sphere(glm::vec3(1.5, -0.5, -18), 3, red_rubber));
    objects.push_back(new Sphere(glm::vec3(7, 5, -18), 4, mirror));
    objects.push_back(new Triangle(std::vector({glm::vec3(-3, -3, -18), glm::vec3(3, -3, -20), glm::vec3(0, 3, -18)}), ivory));

    objects.push_back(new Sphere(glm::vec3(-3, 0, -24), 6, ivory));


    lights.push_back(Light(glm::vec3(-20, 20, 20), 1.5));
    lights.push_back(Light(glm::vec3(10, 15, 10), 1));
    lights.push_back(Light(glm::vec3(0, 0, 0), 0.5));
    lights.push_back(Light(glm::vec3(10, 15, -30), 0.7));

//    lights.push_back(Light(glm::vec3(0, 0, -35), 0.5));

    ray_caster();
    camera.update_p_frame();

    while (!io.closed()) {
        io.draw(camera.get_frame(), camera.get_width(), camera.get_height());
        if (camera.updated()) {
            ray_caster();
            camera.update_p_frame();
        }
    }
    return 0;
}
