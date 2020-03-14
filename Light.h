//
// Created by maxim on 11.03.2020.
//

#ifndef RAYS_LIGHT_H
#define RAYS_LIGHT_H

#include <glm/glm.hpp>
#include <Objects.h>


//class Light {
//    glm::vec3 global_position;
//    float intensity;
//    glm::vec3 position;
//
//public:
//    Light(const glm::vec3 &p, const float &i, const glm::mat4 &view_matrix) : global_position(p),
//                                                                              position(view_matrix * glm::vec4(p, 1)),
//                                                                              intensity(i) {}
//
//    float get_intensity() {
//        return intensity;
//    }
//
//    const glm::vec3 &get_position() {
////        std::cout << position.x << "  " << position.y << "  " << position.z << std::endl;
//        return position;
//    }
//
//    void update_position(const glm::mat4 &view_matrix) {
//        position = view_matrix * glm::vec4(global_position, 1);
//    }
//};

class Basic_Light {
    float intensity;
    glm::vec3 position;

public:
    Basic_Light(const glm::vec3 &p, const float &i) : position(p), intensity(i) {}

    float get_intensity() {
        return intensity;
    }

    const glm::vec3 &get_position() {
        return position;
    }
};

class Light_Object {
protected:
    std::vector<Basic_Light> random_lights;
    float intensity;

public:
    explicit Light_Object(const float &i) : intensity(i) {};

    float get_intensity() {
        return intensity;
    }

    virtual std::vector<Basic_Light> &get_lights(int &pos, int &col) = 0;

    virtual void update_l_position(const glm::mat4 &view_matrix) = 0;

    virtual ~Light_Object() {};
};

class Light_Dot : public Light_Object, public Sphere {
    static float intence_color(float zn, float i) {
        return 1 - 1  / std::exp(i);
    }

public:
    Light_Dot(const glm::vec3 &pos, const float &i, const glm::mat4 &view_matrix) : Light_Object(i), Sphere(pos, 0.1f, Material(glm::vec3(1), {0, 0, 0, 0}, 0, 0, 1.), view_matrix) {
        type = LIGHT;
        random_lights.push_back({position, i});
    };

    std::vector<Basic_Light> &get_lights(int &pos, int &col) override {
        pos = 0;
        col = 1;
        return random_lights;
    }

    void update_l_position(const glm::mat4 &view_matrix) override {
        random_lights.clear();
        this->Sphere::update_position(view_matrix);
//        position = view_matrix * glm::vec4(global_position, 1);
        random_lights.push_back({position, intensity});
    }
};

int num_lights = 50;
class Light_Sphere : public Light_Object, public Sphere {
    std::vector<Basic_Light> random_lights;
public:
    Light_Sphere(const glm::vec3 &pos, float r, float intens, const glm::mat4 &view_matrix)
            : Sphere(pos, r, Material({1, 1, 1}, {0, 0, 0, 0}, 0, 0, 1.), view_matrix), Light_Object(intens) {
        type = LIGHT;
        std::srand(time(NULL));
        random_lights.reserve(num_lights);
        for (int i = 0; i < num_lights; i++) {
//            glm::vec3 rand_vec = {0, 0, 0};
            glm::vec3 rand_vec = glm::normalize(
                    glm::vec3(std::rand() / (float) RAND_MAX - 0.5, std::rand() / (float) RAND_MAX - 0.5, std::rand() / (float) RAND_MAX - 0.5)) * (radius);
            random_lights.push_back(Basic_Light(position + rand_vec, intensity / num_lights));
        }
    }

    void update_l_position(const glm::mat4 &view_matrix) override {
        random_lights.clear();
        this->Sphere::update_position(view_matrix);
        for (int i = 0; i < num_lights; i++) {
//            glm::vec3 rand_vec = {0, 0, 0};
            glm::vec3 rand_vec = glm::normalize(
                    glm::vec3(std::rand() / (float) RAND_MAX - 0.5, std::rand() / (float) RAND_MAX - 0.5, std::rand() / (float) RAND_MAX - 0.5)) * (radius);
            random_lights.push_back(Basic_Light(position + rand_vec, intensity / num_lights));
        }
    }

    std::vector<Basic_Light> &get_lights(int &pos, int &col) override {
        return random_lights;
    }

    ~Light_Sphere() {}
};


#endif //RAYS_LIGHT_H
