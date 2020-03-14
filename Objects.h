//
// Created by maxim on 06.03.2020.
//

#ifndef FIRST_OBJECTS_H
#define FIRST_OBJECTS_H

#include <Material.h>
#include <cmath>
#include <random>
#include "texture.h"


enum Type {
    OBJECT, LIGHT
};

class Object {
protected:
    const Texture *texture;
    Material material;
    glm::vec3 position;
    glm::vec3 global_position;


public:
    Type type;

    Object() : material{}, position{}, global_position{}, type(OBJECT), texture(nullptr) {}

    Object(const glm::vec3 &pos, const glm::mat4 &view_matrix) : material(Material()), texture(nullptr),
                                                                 global_position(pos), position(
                    view_matrix * glm::vec4(pos, 1)), type(OBJECT) {}

    Object(const Material &mat, const glm::vec3 &pos, const glm::mat4 &view_matrix) : material(mat),
                                                                                      global_position(pos), position(
                    view_matrix * glm::vec4(pos, 1)), type(OBJECT), texture(nullptr) {};

    Object(const Material &mat, const glm::vec3 &pos, const glm::mat4 &view_matrix, const Texture *tex) : material(mat),
                                                                                                          global_position(
                                                                                                                  pos),
                                                                                                          position(
                                                                                                                  view_matrix *
                                                                                                                  glm::vec4(
                                                                                                                          pos,
                                                                                                                          1)),
                                                                                                          type(OBJECT),
                                                                                                          texture(tex) {}

    virtual const glm::vec3 *ray_intersect(const Ray &ray, float &t0, glm::vec3 &point, glm::vec3 &N) const = 0;

    const Material &get_material() const {
        return material;
    };

    virtual void update_position(const glm::mat4 &view_matrix) {
        position = view_matrix * glm::vec4(global_position, 1);
    }

    virtual ~Object() = default;
};

class Sphere : public Object {
protected:
    float radius;

    glm::vec3 get_N(const glm::vec3 &point) const {
        return glm::normalize(point - position);
    }

public:
    Sphere() : Object() {}

    Sphere(const glm::vec3 &pos, float r, const glm::mat4 &view_matrix) : Object(Material(), pos, view_matrix),
                                                                          radius(r) {}

    Sphere(const glm::vec3 &pos, float r, const Material &mat, const glm::mat4 &view_matrix) : Object(mat, pos,
                                                                                                      view_matrix),
                                                                                               radius(r) {}

    const glm::vec3 *ray_intersect(const Ray &ray, float &t0, glm::vec3 &point, glm::vec3 &N) const override {
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
        point = ray.get_point(t0);
        N = get_N(point);
        return &material.diffuse_color;
    }
};

class Basic_Triangle {
    glm::vec3 p0, p1, p2;
    glm::vec3 c_p0{}, c_p1{}, c_p2{};
    const Texture *texture;
    glm::vec2 tex_coords;

    glm::vec3 get_N() const {
        return glm::normalize(glm::cross(c_p1 - c_p0, c_p2 - c_p0));
    }

public:
    Basic_Triangle() : p0{}, p1{}, p2{}, texture(nullptr), tex_coords{} {};

    Basic_Triangle(const glm::vec3 &p0_, const glm::vec3 &p1_, const glm::vec3 &p2_, const glm::mat4 &view_matrix) : p0(p0_), p1(p1_),
                                                                                                                     p2(p2_),
                                                                                                                     texture(nullptr),
                                                                                                                     tex_coords{}, c_p0{}, c_p1{}, c_p2{} {
        c_p0 = view_matrix * glm::vec4(p0, 1);
        c_p1 = view_matrix * glm::vec4(p1, 1);
        c_p2 = view_matrix * glm::vec4(p2, 1);
    };

    Basic_Triangle(const std::vector<glm::vec3> &vec, const glm::mat4 &view_matrix) : p0(vec[0]), p1(vec[1]),
                                                                                      p2(vec[2]), texture(nullptr),
                                                                                      tex_coords{} {
        c_p0 = view_matrix * glm::vec4(p0, 1);
        c_p1 = view_matrix * glm::vec4(p1, 1);
        c_p2 = view_matrix * glm::vec4(p2, 1);
    };

    Basic_Triangle(const glm::vec3 &p0_, const glm::vec3 &p1_, const glm::vec3 &p2_, const glm::mat4 &view_matrix,
                   const Texture *tex, const glm::vec3 tex_coord) : texture(tex), tex_coords(tex_coord), p0(p0_), p1(p1_),
            p2(p2_), c_p0{}, c_p1{}, c_p2{} {
        c_p0 = view_matrix * glm::vec4(p0, 1);
        c_p1 = view_matrix * glm::vec4(p1, 1);
        c_p2 = view_matrix * glm::vec4(p2, 1);
    };

    bool ray_intersect(const Ray &ray, float &t0) const {
        const float EPSILON = 0.0000001;
        glm::vec3 vertex0 = c_p0;
        glm::vec3 vertex1 = c_p1;
        glm::vec3 vertex2 = c_p2;
        glm::vec3 edge1, edge2, h, s, q;
        float a, f, u, v;
        edge1 = vertex1 - vertex0;
        edge2 = vertex2 - vertex0;
        h = glm::cross(ray.dir, edge2);
        a = glm::dot(edge1, h);
        if (a > -EPSILON && a < EPSILON)
            return false;
        f = 1.0 / a;
        s = ray.orig - vertex0;
        u = f * glm::dot(s, h);
        if (u < 0.0 || u > 1.0)
            return false;
        q = glm::cross(s, edge1);
        v = f * glm::dot(ray.dir, q);
        if (v < 0.0 || u + v > 1.0)
            return false;
        float t = f * glm::dot(edge2, q);
        if (t > EPSILON) {
            t0 = t;
            return true;
        } else
            return false;
    }

    glm::vec3 get_N() {
        return glm::normalize(glm::cross(c_p1 - c_p0, c_p2 - c_p0)); // Правый обход
    }

    void update_position(const glm::mat4 &view_matrix) {
        c_p0 = view_matrix * glm::vec4(p0, 1);
        c_p1 = view_matrix * glm::vec4(p1, 1);
        c_p2 = view_matrix * glm::vec4(p2, 1);
    }
};

class Chess_Board : public Object {
    glm::vec3 dir0;
    glm::vec3 c_dir0;
    glm::vec3 dir1;
    glm::vec3 c_dir1;
    glm::vec2 edge_len;
    float box_len;

    glm::vec3 get_N() const {
        return glm::normalize(glm::cross(c_dir0, c_dir1));
    }

public:
    Chess_Board(const glm::vec3 &position, const glm::vec3 &dir0_, const glm::vec3 &dir1_, glm::vec2 edge,
                const Material &material, const glm::mat4 &view_matrix) : Object(material, position, view_matrix),
                                                                          dir0(glm::normalize(dir0_)),
                                                                          dir1(glm::normalize(dir1_)), edge_len(edge) {
        c_dir0 = glm::normalize(view_matrix * glm::vec4(dir0, 0));
        c_dir1 = glm::normalize(view_matrix * glm::vec4(dir1, 0));
        box_len = 3;
    }

    const glm::vec3 *ray_intersect(const Ray &ray, float &t0, glm::vec3 &point, glm::vec3 &N) const override {
        glm::vec3 normal = get_N();
        float t = -glm::dot(ray.orig - position, normal) / glm::dot(ray.dir, normal);
        t0 = t;
        if (t < 0.001)
            return nullptr;
        point = ray.get_point(t0);
        N = normal;

        glm::vec3 n_dir0 = c_dir0 * edge_len[0];
        glm::vec3 n_dir1 = c_dir1 * edge_len[1];

        glm::vec3 a = point - position;

        float n = glm::dot(n_dir0, n_dir0) / glm::dot((point - position), n_dir0);
        float k = glm::dot(n_dir1, n_dir1) / glm::dot((point - position), n_dir1);

        if (std::fabs(n) < 1) {
            return nullptr;
        }

        if (std::fabs(k) < 1) {
            return nullptr;
        }

        float cos0 = glm::dot(glm::normalize(a), c_dir0);
        float cos1 = glm::dot(glm::normalize(a), c_dir1);

        float coord0 = glm::length(a * cos0);
        float coord1 = glm::length(a * cos1);

        auto fmod = [](float val, int mod) {
            return val - std::floor(val / mod) * mod;
        };

        coord0 = fmod(fmod(coord0, 2 * box_len) + ((cos0 < 0) ? box_len : 0), box_len * 2);
        coord1 = fmod(fmod(coord1, 2 * box_len) + ((cos1 < 0) ? box_len : 0), box_len * 2);
        return &material.diffuse_color;
//        if (coord0 < box_len) {
//            if (coord1 < box_len) {
//                return new glm::vec3(0., 0., 0.);
//            } else {
//                return new glm::vec3(1., 1, 1.);
//            }
//        }
//        else {
//            if (coord1 > box_len) {
//                return new glm::vec3(0., 0., 0.);
//            } else {
//                return new glm::vec3(1., 1, 1.);
//            }
//        }
//        return new glm::vec3(color);
    }

    void update_position(const glm::mat4 &view_matrix) override {
        c_dir0 = glm::normalize(view_matrix * glm::vec4(dir0, 0));
        c_dir1 = glm::normalize(view_matrix * glm::vec4(dir1, 0));
        position = view_matrix * glm::vec4(global_position, 1);
    }

};

class Object_From_File : public Object {
private:
    float scale;
    std::vector<Basic_Triangle *> triangles;
    glm::vec3 x, z;

    void init_triangles(const char *file_name, const glm::mat4 &view_matrix) {
        std::vector<glm::vec3> vertices;
        std::vector<int> indices;
        std::ifstream str(file_name);
        std::string type;

        glm::vec3 x_w = {1, 0, 0};
        glm::vec3 z_w = {0, 0, 1};

        float alpha = glm::dot(x, x_w);


        glm::mat4 rot{1};
        if (alpha != 1) {
            rot = glm::rotate(rot, std::acos(alpha), glm::cross(x, x_w));
        }
        glm::vec3 z_sh = rot * glm::vec4(z, 0);

        float beta = glm::dot(glm::normalize(z_sh), z_w);

        glm::mat4 sc = glm::scale(glm::mat4{1}, glm::vec3(scale, scale, scale));
        rot = glm::rotate(rot, std::acos(beta), x_w);
        glm::mat4 trans = glm::translate(glm::mat4{1}, global_position);

        float p1, p2, p3;
        while (str >> type >> p1 >> p2 >> p3) {
            if (type == "v") {
                vertices.push_back(trans * rot * sc * glm::vec4(glm::vec3(p1, p2, p3), 1));
//                std::cout << vertices[vertices.size() - 1].x << " " << vertices[vertices.size() - 1].y << " " << vertices[vertices.size() - 1].z;
            } else {
                indices.push_back(p1);
                indices.push_back(p2);
                indices.push_back(p3);
            };
        }
        for (int i = 0; i < indices.size(); i += 3)
            triangles.push_back(
                    new Basic_Triangle(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]],
                                       view_matrix));
        str.close();
    }

public:

    Object_From_File() : Object(), scale{}, x{}, z{} {};

    Object_From_File(const glm::vec3 &pos, float sc, const Material &mat, const glm::mat4 &view_matrix,
                     const char *file_name, const Texture *t = nullptr) : Object(mat, pos,
                                                                                 view_matrix, t),
                                                                          scale(sc),
                                                                          triangles{}, x(1, 0, 0), z(0, 0, 1) {
        init_triangles(file_name, view_matrix);
    }

    Object_From_File(const glm::vec3 &pos, const glm::vec3 &x_, const glm::vec3 &z_, float sc, const Material &mat,
                     const glm::mat4 &view_matrix, const char *file_name, const Texture *t = nullptr)
            : Object_From_File(pos, sc, mat, view_matrix, file_name, t) {
        x = glm::normalize(x_);
        z = glm::normalize(z_);
        triangles.clear();
        init_triangles(file_name, view_matrix);
    }

    const glm::vec3 *ray_intersect(const Ray &ray, float &t0, glm::vec3 &point, glm::vec3 &N) const override {
        Basic_Triangle *interTriangle = nullptr;
        float objects_dist = std::numeric_limits<float>::max();
        for (auto tr : triangles) {
            float dist_i;
            const glm::vec3 *col;
            if (tr->ray_intersect(ray, dist_i) && dist_i < objects_dist) {
                objects_dist = dist_i;
                interTriangle = tr;
            }
        }
        if (!interTriangle)
            return nullptr;
        t0 = objects_dist;
        point = ray.get_point(t0);
        N = interTriangle->get_N();
        return &material.diffuse_color;
    }

    void update_position(const glm::mat4 &view_matrix) override {
        position = view_matrix * glm::vec4(global_position, 1);
        for (auto tr : triangles)
            tr->update_position(view_matrix);
    }

    ~Object_From_File() {
        for (auto tr : triangles)
            delete tr;
    }
};




//class Cylinder : public Object {
//
//};
//
//class Cube : public Object {
//private:
//    float edge_len;
//    std::vector<Basic_Triangle *> triangles;
//public:
//    Cube() : Object() {};
//
//    Cube(const glm::vec3 &pos, float len, const Material &mat, const glm::mat4 &view_matrix) : Object(mat, pos,
//                                                                                                      view_matrix),
//                                                                                               edge_len(len),
//                                                                                               triangles{} {
//        std::vector<glm::vec3> vertices{};
//        int is[] = {-1, 1};
//        for (int x : is)
//            for (int y : is)
//                for (int z : is)
//                    vertices.push_back(glm::vec3(pos.x + x * edge_len / 2, pos.y + y * edge_len / 2, pos.z + z * edge_len / 2));
//        int indices[] = {
//                1, 5, 7,
//                7, 3, 1,
//                5, 4, 6,
//                6, 7, 5,
//                4, 0, 2,
//                2, 6, 4,
//                0, 1, 3,
//                3, 2, 0,
//                3, 7, 6,
//                6, 2, 3,
//                4, 0, 1,
//                1, 5, 4,
//        };
//        for (int i = 0; i < 6 * 6; i += 3)
//            triangles.push_back(
//                    new Basic_Triangle(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]],
//                                       view_matrix));
//    }
//
//    const glm::vec3 *ray_intersect(const Ray &ray, float &t0, glm::vec3 &point, glm::vec3 &N) const override {
//        Basic_Triangle *interTriangle = nullptr;
//        float objects_dist = std::numeric_limits<float>::max();
//        for (auto tr : triangles) {
//            float dist_i;
//            const glm::vec3 *col;
//            if (tr->ray_intersect(ray, dist_i) && dist_i < objects_dist) {
//                objects_dist = dist_i;
//                interTriangle = tr;
//            }
//        }
//        if (!interTriangle)
//            return nullptr;
//        t0 = objects_dist;
//        point = ray.get_point(t0);
//        N = interTriangle->get_N();
//        return &material.diffuse_color;
//    }
//
//    void update_position(const glm::mat4 &view_matrix) override {
//        position = view_matrix * glm::vec4(global_position, 1);
//        for (auto tr : triangles)
//            tr->update_position(view_matrix);
//    }
//
//    ~Cube() {
//        for (auto tr : triangles)
//            delete tr;
//    }
//};
#endif //FIRST_OBJECTS_H
