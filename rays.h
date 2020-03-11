//
// Created by maxim on 11.03.2020.
//

#ifndef RAYS_RAYS_H
#define RAYS_RAYS_H

#include <glm/glm.hpp>

class Ray {
public:

    glm::vec3 orig;
    glm::vec3 dir;
    Ray(const glm::vec3 &orig_, const glm::vec3 &dir_) : orig(orig_), dir(dir_) {}

    Ray reflect(const glm::vec3 &N, const glm::vec3 &point) const {
        glm::vec3 reflect_dir = dir - N * 2.f * glm::dot(dir, N);
        glm::vec3 reflect_orig = glm::dot(reflect_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f;
        return Ray(reflect_orig, reflect_dir);
    }

    Ray refract(const glm::vec3 &N, const float &refractive_index, const glm::vec3 &point) const { // Snell's law
        float cosi = -std::max(-1.f, std::min(1.f, glm::dot(dir, N)));
        float etai = 1, etat = refractive_index;
        glm::vec3 n = N;
        if (cosi < 0) {
            cosi = -cosi;
            std::swap(etai, etat);
            n = -N;
        }
        float eta = etai / etat;
        float k = 1 - eta * eta * (1 - cosi * cosi);
        glm::vec3 refract_dir = k < 0 ? glm::vec3(0, 0, 0) : dir * eta + n * (eta * cosi - sqrtf(k));
        glm::vec3 refract_orig = glm::dot(refract_dir, N) < 0 ? point - N * 1e-3f : point + N * 1e-3f;
        return Ray(refract_orig, refract_dir);
    }

    glm::vec3 get_point(float dist_i) const {
        return orig + dir * dist_i;
    }


};

#endif //RAYS_RAYS_H
