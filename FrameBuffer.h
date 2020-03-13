//
// Created by maxim on 05.03.2020.
//

#ifndef FIRST_FRAMEBUFFER_H
#define FIRST_FRAMEBUFFER_H

#include <vector>
#include <glm/glm.hpp>
#include <thread>

#define ANTIALIASING 1
#define GAMMA_CORRECTION 1.4
#define CONV 3

//glm::mat3 conv = glm::mat2(1, 0, 1, 0) / 2.f;
glm::mat3 conv = glm::mat3(2, 2, 2, 2, 1, 2, 2, 2, 2) / 17.f;

class frameBuffer {
    std::vector<glm::vec3> frame;
    int width, height;
    int aliased_width, aliased_height;
    unsigned char *p_frame;

    static void conv_one_row(frameBuffer *fr, int i) {
        for (int j = 0; j < fr->aliased_width; j += 1) {
            glm::vec3 col{0};
            for (int k = 0; k < CONV; k++) {
                for (int p = 0; p < CONV; p++) {
                    int coordW = j + p - CONV / 2;
                    int coordH = i + k - CONV / 2;
                    if (coordW < 0 || coordW >= fr->aliased_width || coordH < 0 || coordH >= fr->aliased_height)
                        continue;
                    col += (*fr)(coordH, coordW) * conv[p][k];
                }
            }

            col.r = std::pow(col.r, GAMMA_CORRECTION);
            col.g = std::pow(col.g, GAMMA_CORRECTION);
            col.b = std::pow(col.b, GAMMA_CORRECTION);

            fr->p_frame[3 * (fr->aliased_width * i + j) + 0] = (unsigned char) std::floor(255 * col.r);
            fr->p_frame[3 * (fr->aliased_width * i + j) + 1] = (unsigned char) std::floor(255 * col.g);
            fr->p_frame[3 * (fr->aliased_width * i + j) + 2] = (unsigned char) std::floor(255 * col.b);
        }
    }

    static void one_row(frameBuffer *fr, int i, int i_fr) {
        for (int j = 0, j_fr = 0; j < fr->aliased_width; j += 1, j_fr += ANTIALIASING) {
            fr->p_frame[3 * (fr->aliased_width * i + j) + 0] = 0;
            fr->p_frame[3 * (fr->aliased_width * i + j) + 1] = 0;
            fr->p_frame[3 * (fr->aliased_width * i + j) + 2] = 0;
            float r = 0, g = 0, b = 0;
            for (int k = 0; k < ANTIALIASING; k++) {
                for (int p = 0; p < ANTIALIASING; p++) {
                    r += fr->frame[(i_fr + k) * fr->width + j_fr + p].r;
                    g += fr->frame[(i_fr + k) * fr->width + j_fr + p].g;
                    b += fr->frame[(i_fr + k) * fr->width + j_fr + p].b;
                }
            }
            r = std::pow(r / ANTIALIASING / ANTIALIASING, GAMMA_CORRECTION);
            g = std::pow(g / ANTIALIASING / ANTIALIASING, GAMMA_CORRECTION);
            b = std::pow(b / ANTIALIASING / ANTIALIASING, GAMMA_CORRECTION);

            fr->p_frame[3 * (fr->aliased_width * i + j) + 0] = (unsigned char) std::floor(255 * r);
            fr->p_frame[3 * (fr->aliased_width * i + j) + 1] = (unsigned char) std::floor(255 * g);
            fr->p_frame[3 * (fr->aliased_width * i + j) + 2] = (unsigned char) std::floor(255 * b);
        }
    }
public:
    const unsigned char *get_frame() {
        return p_frame;
    }

    void update_p_frame() {

        std::vector<std::thread> threads;
        threads.reserve(aliased_height);
        for (int i = 0; i < aliased_height; i++) {
            threads.emplace_back(conv_one_row, this, i);
        }
        for (auto &t : threads) {
            t.join();
        }

//        std::vector<std::thread> threads;
//        threads.reserve(aliased_height);
//        for (int i = 0, i_fr = 0; i < aliased_height; i++, i_fr += ANTIALIASING) {
//            threads.emplace_back(one_row, this, i, i_fr);
//        }
//        for (auto &t : threads) {
//            t.join();
//        }
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

    int get_aliased_width() const {
        return aliased_width;
    }

    int get_aliased_height() const {
        return aliased_height;
    }



    frameBuffer(int w, int h) : width(w * ANTIALIASING), height(h * ANTIALIASING), aliased_width(w), aliased_height(h) {
        p_frame = new unsigned char[aliased_width * aliased_height * 3];
        frame = std::vector<glm::vec3>(width * height);
    }

    ~frameBuffer() {
        delete p_frame;
    }
};

#endif //FIRST_FRAMEBUFFER_H
