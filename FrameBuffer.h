//
// Created by maxim on 05.03.2020.
//

#ifndef FIRST_FRAMEBUFFER_H
#define FIRST_FRAMEBUFFER_H

#include <vector>
#include <glm/glm.hpp>

class frameBuffer {
    std::vector<glm::vec3> frame;
    int width, height;
    unsigned char *p_frame;
public:
    const unsigned char *get_frame() {
        return p_frame;
    }

    void update_p_frame() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                p_frame[3 * (width * i + j) + 0] = (unsigned char) floor(255 * frame[i * width + j].r);
                p_frame[3 * (width * i + j) + 1] = (unsigned char) floor(255 * frame[i * width + j].g);
                p_frame[3 * (width * i + j) + 2] = (unsigned char) floor(255 * frame[i * width + j].b);
            }
        }
    }

    glm::vec3 &operator()(int i, int j) {
        return frame[i * width + j];
    }

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }

    frameBuffer(int w, int h) : width(w), height(h) {
        p_frame = new unsigned char[w * h * 3];
        frame = std::vector<glm::vec3>(w * h);
    }

    ~frameBuffer() {
        delete p_frame;
    }
};

#endif //FIRST_FRAMEBUFFER_H
