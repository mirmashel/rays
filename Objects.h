//
// Created by maxim on 06.03.2020.
//

#ifndef FIRST_OBJECTS_H
#define FIRST_OBJECTS_H

#include <Material.h>

class Object {
protected:
    Material material;
    glm::vec3 position;


public:
    Object() : material{}, position{} {}

    Object(Material mat, glm::vec3 pos) : material(mat), position(pos) {}

    virtual const glm::vec3 *
    ray_intersect(const glm::vec3 &orig, const glm::vec3 &dir, float &t0, const glm::mat4 &view_matrix) const = 0;

//    virtual const glm::vec3 &get_color() const = 0;

    virtual const glm::vec3 get_N(const glm::vec3 point, const glm::mat4 &view_matrix) const = 0;

    const Material &get_material() const {
        return material;
    };
};

class Sphere : public Object {
    float radius;


public:
    Sphere() : Object() {}

    Sphere(glm::vec3 pos, float r, Material mat) : Object(mat, pos), radius(r) {}

    const glm::vec3 *ray_intersect(const glm::vec3 &orig, const glm::vec3 &dir, float &t0, const glm::mat4 &view_matrix) const override {
        glm::vec3 new_center = view_matrix * glm::vec4(position, 1);
        glm::vec3 L = new_center - orig;
        float tca = glm::dot(L, dir);
        float d2 = glm::dot(L, L) - glm::dot(tca, tca);
        if (d2 > radius * radius) return nullptr;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0)
            t0 = t1;
        if (t0 < 0)
            return nullptr;
        return &material.diffuse_color;
    }

    const glm::vec3 get_N(const glm::vec3 point, const glm::mat4 &view_matrix) const override {
        return glm::normalize(point - glm::vec3(view_matrix * glm::vec4(position, 1)));
    }
};

class Triangle : public Object {
    glm::vec3 p1, p2, p3;
    Material material;
public:
    Triangle() : p1{}, p2{}, p3{}, material{} {};

    Triangle(glm::vec3 p1_, glm::vec3 p2_, glm::vec3 p3_, Material &mat) : p1(p1_), p2(p2_), p3(p3_), material(mat) {};

    Triangle(std::vector<glm::vec3> vec, Material &mat) : p1(vec[0]), p2(vec[1]), p3(vec[2]), material(mat) {};

    const glm::vec3 *ray_intersect(const glm::vec3 &orig, const glm::vec3 &dir, float &t0, const glm::mat4 &view_matrix) const override {
        glm::vec3 v0 = view_matrix * glm::vec4(p1, 1);
        glm::vec3 v1 = view_matrix * glm::vec4(p2, 1);
        glm::vec3 v2 = view_matrix * glm::vec4(p3, 1);

        glm::vec3 e1 = v1 - v0;
        glm::vec3 e2 = v2 - v0;
        // Вычисление вектора нормали к плоскости
        glm::vec3 pvec = cross(dir, e2);
        float det = dot(e1, pvec);

        // Луч параллелен плоскости
        if (det < 1e-8 && det > -1e-8) {
            t0 = 0.0f;
            return nullptr;
        }

        float inv_det = 1 / det;
        glm::vec3 tvec = orig - v0;
        float u = dot(tvec, pvec) * inv_det;
        if (u < 0 || u > 1) {
            t0 = 0.0f;
            return nullptr;
        }

        glm::vec3 qvec = cross(tvec, e1);
        float v = dot(dir, qvec) * inv_det;
        if (v < 0 || u + v > 1) {
            t0 = 0.0f;
            return nullptr;
        }
        t0 = dot(e2, qvec) * inv_det;
        return &material.diffuse_color;
    }

    const glm::vec3 get_N(const glm::vec3 point, const glm::mat4 &view_matrix) const override {
        glm::vec3 v0 = view_matrix * glm::vec4(p1, 1);
        glm::vec3 v1 = view_matrix * glm::vec4(p2, 1);
        glm::vec3 v2 = view_matrix * glm::vec4(p3, 1);
        return -glm::normalize(glm::cross(v1 - v0, v2 - v0));
    }

};


#endif //FIRST_OBJECTS_H
