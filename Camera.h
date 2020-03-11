//
// Created by maxim on 05.03.2020.
//

#ifndef FIRST_CAMERA_H
#define FIRST_CAMERA_H

#include <FrameBuffer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <rays.h>

class Camera {
    frameBuffer frame; // screen
    GLfloat fov; // field_of_view, radians
    glm::vec3 position; // center of focus
    glm::vec3 direction; // direction of view
    glm::vec3 orientation;
    bool upd = false;

    float ratio;

    glm::vec3 get_norm_coords(int i, int j) {
        if (ratio < 1) {
            float x = (2.0f * j + 1.0f - frame.get_width()) / frame.get_width();
            float y = (2.0f * i + 1.0f - frame.get_height()) / frame.get_height() * ratio;
            float z = 1.0f / tan(fov / 2.0f);
            return glm::normalize(glm::vec3(x, y, -z));
        } else {
            float x = (2.0f * j + 1.0f - frame.get_width()) / frame.get_width() / ratio;
            float y = (2.0f * i + 1.0f - frame.get_height()) / frame.get_height();
            float z = 1.0f / tan(fov / 2.0f);
            return glm::normalize(glm::vec3(x, y, -z));
        }
    }

public:

    Camera(int w = 720,
           int h = 480,
           int fv = M_PI / 2.,
           glm::vec3 pos = glm::vec3(0),
           glm::vec3 dir = glm::vec3(0, 0, -1),
           glm::vec3 orient = glm::vec3(0, 1, 0)
    ) : frame(w, h), fov(fv), position(pos), direction(dir), orientation(orient), ratio((float) h / w) {}

    glm::mat4 get_view_matrix() {
        glm::mat4 view(1.0);
        return glm::lookAt(position,
                           position + direction,
                           orientation);
    }

    std::vector<Ray> generate_rays() {
        std::vector<Ray> rays;
        for (int i = 0; i < frame.get_height(); i++) {
            for (int j = 0; j < frame.get_width(); j++) {
                rays.push_back(Ray({0, 0, 0}, get_norm_coords(i, j)));
            }
        }
        return rays;
    }

    int get_width() const {
        return frame.get_width();
    }

    int get_height() const {
        return frame.get_height();
    }

    glm::vec3 &operator()(int i, int j) {
        return frame(i, j);
    }

    void update_p_frame() {
        frame.update_p_frame();
    }

    const unsigned char *get_frame() {
        return frame.get_frame();
    }

    void move(int key, int action, int mode) {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_UP) {
                position += glm::normalize(orientation);
            }
            if (key == GLFW_KEY_RIGHT) {
                position += glm::normalize(glm::cross(direction, orientation));
            }
            if (key == GLFW_KEY_DOWN) {
                position -= glm::normalize(orientation);
            }
            if (key == GLFW_KEY_LEFT) {
                position -= glm::normalize(glm::cross(direction, orientation));
            }
            if (key == GLFW_KEY_W) {
                position += glm::normalize(direction);
            }
            if (key == GLFW_KEY_S) {
                position -= glm::normalize(direction);
            }
            if (key == GLFW_KEY_D) {
                glm::mat4 rot(1);
                rot = glm::rotate(rot, -0.1f, orientation);
                direction = rot * glm::vec4(direction, 1);
            }
            if (key == GLFW_KEY_A) {
                glm::mat4 rot(1);
                rot = glm::rotate(rot, 0.1f, orientation);
                direction = rot * glm::vec4(direction, 1);
            }
            if (key == GLFW_KEY_E) {
                glm::mat4 rot(1);
                rot = glm::rotate(rot, -0.1f, direction);
                orientation = rot * glm::vec4(orientation, 1);
            }
            if (key == GLFW_KEY_Q) {
                glm::mat4 rot(1);
                rot = glm::rotate(rot, 0.1f, direction);
                orientation = rot * glm::vec4(orientation, 1);
            }
            if (key == GLFW_KEY_R) {
                glm::mat4 rot(1);
                rot = glm::rotate(rot, 0.1f, glm::cross(direction, orientation));
                direction = rot * glm::vec4(direction, 1);
                orientation = rot * glm::vec4(orientation, 1);
            }
            if (key == GLFW_KEY_F) {
                glm::mat4 rot(1);
                rot = glm::rotate(rot, -0.1f, glm::cross(direction, orientation));
                direction = rot * glm::vec4(direction, 1);
                orientation = rot * glm::vec4(orientation, 1);
            }
            upd = true;
        }
    }

    bool updated() {
        if (upd) {
            upd = false;
            return true;
        }
        return upd;
    }

};

#endif //FIRST_CAMERA_H
