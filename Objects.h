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
    glm::vec3 global_position;

public:
    Object() : material{}, position{}, global_position{} {}

    Object(const Material &mat, const glm::vec3 &pos, const glm::mat4 &view_matrix) : material(mat), global_position(pos), position(view_matrix * glm::vec4(pos, 1)) {}

    virtual const glm::vec3 *
    ray_intersect(const Ray &ray, float &t0, const glm::mat4 &view_matrix) const = 0;

//    virtual const glm::vec3 &get_color() const = 0;

    virtual const glm::vec3 get_N(const glm::vec3 &point, const glm::mat4 &view_matrix) const = 0;

    const Material &get_material() const {
        return material;
    };

    void update_position(const glm::mat4 &view_matrix) {
        position = view_matrix * glm::vec4(global_position, 1);
    }
};

class Sphere : public Object {
    float radius;


public:
    Sphere() : Object() {}

    Sphere(const glm::vec3 &pos, float r, const Material &mat, const glm::mat4 &view_matrix) : Object(mat, pos, view_matrix), radius(r) {}

    const glm::vec3 *ray_intersect(const Ray &ray, float &t0, const glm::mat4 &view_matrix) const override {
//        std::cout << position.x << "  " << position.y << "  " << position.z << std::endl;
        glm::vec3 new_center = position;
        glm::vec3 L = new_center - ray.orig;
        float tca = glm::dot(L, ray.dir);
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

    const glm::vec3 get_N(const glm::vec3 &point, const glm::mat4 &view_matrix) const override {
        return glm::normalize(point - position);
    }
};

//class Triangle : public Object {
//    glm::vec3 p1, p2, p3;
//public:
//    Triangle() : p1{}, p2{}, p3{} {};
//
//    Triangle(glm::vec3 p1_, glm::vec3 p2_, glm::vec3 p3_, Material &mat) : Object(), p1(p1_), p2(p2_), p3(p3_) {};
//
//    Triangle(std::vector<glm::vec3> vec, Material &mat) : Object(mat, {0, 0, 0}, glm::mat4(0)), p1(vec[0]), p2(vec[1]), p3(vec[2]) {};
//
//    const glm::vec3 *ray_intersect(const glm::vec3 &orig, const glm::vec3 &dir, float &t0, const glm::mat4 &view_matrix) const override {
//        glm::vec3 v0 = view_matrix * glm::vec4(p1, 1);
//        glm::vec3 v1 = view_matrix * glm::vec4(p2, 1);
//        glm::vec3 v2 = view_matrix * glm::vec4(p3, 1);
//
//        glm::vec3 e1 = v1 - v0;
//        glm::vec3 e2 = v2 - v0;
//        // Вычисление вектора нормали к плоскости
//        glm::vec3 pvec = cross(dir, e2);
//        float det = dot(e1, pvec);
//
//        // Луч параллелен плоскости
//        if (det < 1e-8 && det > -1e-8) {
//            t0 = 0.0f;
//            return nullptr;
//        }
//
//        float inv_det = 1 / det;
//        glm::vec3 tvec = orig - v0;
//        float u = dot(tvec, pvec) * inv_det;
//        if (u < 0 || u > 1) {
//            t0 = 0.0f;
//            return nullptr;
//        }
//
//        glm::vec3 qvec = cross(tvec, e1);
//        float v = dot(dir, qvec) * inv_det;
//        if (v < 0 || u + v > 1) {
//            t0 = 0.0f;
//            return nullptr;
//        }
//        t0 = dot(e2, qvec) * inv_det;
//        return &material.diffuse_color;
//    }
//
//    const glm::vec3 get_N(const glm::vec3 point, const glm::mat4 &view_matrix) const override {
//        glm::vec3 v0 = view_matrix * glm::vec4(p1, 1);
//        glm::vec3 v1 = view_matrix * glm::vec4(p2, 1);
//        glm::vec3 v2 = view_matrix * glm::vec4(p3, 1);
//        return glm::normalize(glm::cross(v1 - v0, v2 - v0));
//    }
//
//};


#endif //FIRST_OBJECTS_H
