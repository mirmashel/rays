//
// Created by maxim on 11.03.2020.
//

#ifndef RAYS_RAYS_H
#define RAYS_RAYS_H

#include <glm/glm.hpp>
#include "Randomizer.h"

#define EPS 1e-3f

extern Randomizer randomizer;

glm::vec3 reflect(const glm::vec3 &I, const glm::vec3 &N) {
    return I - N * 2.f * glm::dot(I,N);
}

class Ray {
public:

    glm::vec3 orig;
    glm::vec3 dir;
    Ray(const glm::vec3 &orig_, const glm::vec3 &dir_) : orig(orig_), dir(glm::normalize(dir_)) {}

    Ray reflect(const glm::vec3 &N, const glm::vec3 &point) const {
        glm::vec3 reflect_dir = dir - N * 2.f * glm::dot(dir, N);
        glm::vec3 reflect_orig = glm::dot(reflect_dir, N) < 0 ? point - N * EPS : point + N * EPS;
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
        glm::vec3 refract_orig = glm::dot(refract_dir, N) < 0 ? point - N * EPS : point + N * EPS;
        return Ray(refract_orig, refract_dir);
    }

    glm::vec3 get_point(float dist_i) const {
        return orig + dir * dist_i;
    }

    glm::mat3 GetTangentSpace(const glm::vec3 &normal) const {
        // Выбираем вспомогательный вектор для векторного произведения
        glm::vec3 helper = glm::vec3(1, 0, 0);
        if (abs(normal.x) > 0.99f)
            helper = glm::vec3(0, 0, 1);

        // Генерируем векторы
        glm::vec3 tangent = glm::normalize(glm::cross(normal, helper));
        glm::vec3 binormal = glm::normalize(glm::cross(normal, tangent));
        return glm::mat3(tangent, binormal, normal);
    }

    Ray new_random_ray(const glm::vec3 &N, const glm::vec3 &point) const {
        auto r1 = (float) randomizer.get_random();
        auto r2 = (float) randomizer.get_random();
//        std::cout << r1 << " " << r2 << std::endl;
        float phi = 2 * M_PI * r1;
        float h = 2 * r2 - 1;
        glm::vec3 new_dir(std::sin(phi) * std::sqrt(1 - h * h), std::cos(phi) * std::sqrt(1 - h * h), h);
        glm::vec3 new_orig = glm::dot(new_dir, N) < 0 ? point - N * EPS : point + N * EPS;
        if (glm::dot(new_dir, N) < 0)
            new_dir = -new_dir;
        return {new_orig, new_dir};

//        float cosTheta = randomizer.get_random();
//        float sinTheta = sqrt(std::max(0.0f, 1.0f - cosTheta * cosTheta));
//        float phi = 2 * M_PI * randomizer.get_random();
//        glm::vec3 tangentSpaceDir = glm::vec3(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
//        glm::vec3 new_dir = tangentSpaceDir * GetTangentSpace(N);
//        glm::vec3 new_orig = glm::dot(new_dir, N) < 0 ? point - N * EPS : point + N * EPS;
//        if (glm::dot(new_dir, N) < 0)
//            new_dir = -new_dir;
//        return {new_orig, new_dir};


//        glm::vec3 new_orig = glm::dot(new_dir, N) < 0 ? point - N * EPS : point + N * EPS;

//        glm::vec3 new_dir = glm::normalize(glm::vec3(std::rand() + EPS, std::rand(), std::rand()) / (float) RAND_MAX);
//        return {new_orig, new_dir};
    }
};

#endif //RAYS_RAYS_H
