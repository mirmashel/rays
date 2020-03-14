//
// Created by maxim on 13.03.2020.
//

#ifndef RAYS_TEXTURE_H
#define RAYS_TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <glm/glm.hpp>
#include <iostream>

class Texture {
private:
    int w, h, c;
    unsigned char *image;

    int get_w_coord(float w_coord) const {
        return ((int) std::floor(w_coord) + w) % w;
    }

    int get_h_coord(float h_coord) const {
        return ((int) std::floor(h_coord) + h) % h;
    }

public:

    Texture(const char *picture_name) {
        image = stbi_load(picture_name, &w, &h, &c, STBI_rgb);
        if (!image)
            std::cout << "Problema s kartinkoy" << std::endl;
    }

    glm::vec3 get_pixel_color(glm::vec2 coords) const { // x, y E (0, 1),
        coords *= glm::vec2(h, w);
        int c_h = coords.x;
        int c_w = coords.y;
//        std::cout << c_h << " " << c_w << std::endl;
        glm::vec2 coords1 = coords + glm::vec2(0.5, 0.5),
                coords2 = coords + glm::vec2(0.5, -0.5),
                coords3 = coords + glm::vec2(-0.5, 0.5),
                coords4 = coords + glm::vec2(-0.5, -0.5);

//        return glm::vec3(image[3 * (w * c_h + c_w) + 0], image[3 * (w * c_h + c_w) + 1], image[3 * (w * c_h + c_w) + 2]) / 255.f;

        return (glm::vec3(
                image[3 * (w * get_h_coord(coords1.x) + get_w_coord(coords1.y)) + 0],
                image[3 * (w * get_h_coord(coords1.x) + get_w_coord(coords1.y)) + 1],
                image[3 * (w * get_h_coord(coords1.x) + get_w_coord(coords1.y)) + 2]
        ) + glm::vec3(
                image[3 * (w * get_h_coord(coords2.x) + get_w_coord(coords2.y)) + 0],
                image[3 * (w * get_h_coord(coords2.x) + get_w_coord(coords2.y)) + 1],
                image[3 * (w * get_h_coord(coords2.x) + get_w_coord(coords2.y)) + 2]
        ) + glm::vec3(
                image[3 * (w * get_h_coord(coords3.x) + get_w_coord(coords3.y)) + 0],
                image[3 * (w * get_h_coord(coords3.x) + get_w_coord(coords3.y)) + 1],
                image[3 * (w * get_h_coord(coords3.x) + get_w_coord(coords3.y)) + 2]
        ) + glm::vec3(
                image[3 * (w * get_h_coord(coords4.x) + get_w_coord(coords4.y)) + 0],
                image[3 * (w * get_h_coord(coords4.x) + get_w_coord(coords4.y)) + 1],
                image[3 * (w * get_h_coord(coords4.x) + get_w_coord(coords4.y)) + 2]
        )) / 255.f / 4.f;

    }

    ~Texture() {
        stbi_image_free(image);
    }
};

#endif //RAYS_TEXTURE_H
