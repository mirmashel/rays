//
// Created by maxim on 11.03.2020.
//

#ifndef RAYS_LIGHT_H
#define RAYS_LIGHT_H

#include <glm/glm.hpp>

class Light {
    glm::vec3 global_position;
    float intensity;
    glm::vec3 position;

public:
    Light(const glm::vec3 &p, const float &i, const glm::mat4 &view_matrix) : global_position(p),
                                                                              position(view_matrix * glm::vec4(p, 1)),
                                                                              intensity(i) {}

    float get_intensity() {
        return intensity;
    }

    const glm::vec3 &get_position() {
//        std::cout << position.x << "  " << position.y << "  " << position.z << std::endl;
        return position;
    }

    void update_position(const glm::mat4 &view_matrix) {
        position = view_matrix * glm::vec4(global_position, 1);
    }
};


#endif //RAYS_LIGHT_H
