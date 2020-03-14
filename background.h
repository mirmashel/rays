//
// Created by maxim on 13.03.2020.
//

#ifndef RAYS_BACKGROUND_H
#define RAYS_BACKGROUND_H

//#include <stb_image.h>
#include <rays.h>
#include <glm/glm.hpp>
#include <texture.h>

class Background {
//    int w, h, c;
//    unsigned char *image;
Texture texture;
    glm::mat4 rot;

public:
    Background(const char *picture_name, const glm::mat4 &view_matrix) : texture(picture_name) {
//        stbi_set_flip_vertically_on_load(true);
        rot = glm::mat4(1);
        rot = glm::rotate(rot, (float) M_PI / 2, glm::vec3(1, 0, 0));
        rot = glm::rotate(rot, (float) M_PI / 2, glm::vec3(0, 1, 0));
        rot = rot * glm::inverse(view_matrix);
    }

    glm::vec3 pixel_color(const Ray &ray) {
//        return {0.2, 0.7, 0.8};

        const glm::vec3 dir = rot * glm::vec4(ray.dir, 0);
//        std::cout << dir.x << " " << dir.y << " " << dir.z << std::endl;
//        if (std::isnan(dir.x) || std::isnan(dir.y) || std::isnan(dir.z))// || std::isnan(dir.x))
//            return glm::vec3(image[3 * (w * 0 + 0) + 0], image[3 * (w * 0 + 0) + 1], image[3 * (w * 0 + 0) + 2]) / 255.f;
        float t = -std::atan(dir.z / std::sqrt(dir.x * dir.x + dir.y * dir.y)) + M_PI / 2.f;
        float phi = std::atan(dir.y / (dir.x));

//        std::cout << t << " " << phi << std::endl;
        if (std::isnan(t) || std::isnan(phi))
            return texture.get_pixel_color({0, 0});

        if (dir.x > 0 && dir.y > 0)
            phi += 0;
        else if (dir.x <= 0)
            phi += M_PI;
        else
            phi += 2 * M_PI;


        return texture.get_pixel_color({t / M_PI, 1 - phi / 2 / M_PI});
//        int c_h = (int) std::floor((t / M_PI) * h);
//        int c_w = w - 1 - (int) std::floor( (phi / 2 / M_PI) * w);
//        return glm::vec3(image[3 * (w * c_h + c_w) + 0], image[3 * (w * c_h + c_w) + 1], image[3 * (w * c_h + c_w) + 2]) / 255.f;
    }

    void update(const glm::mat4 &view_matrix) {
        rot = glm::mat4(1);
        rot = glm::rotate(rot, (float) M_PI / 2, glm::vec3(1, 0, 0));
        rot = glm::rotate(rot, (float) M_PI / 2, glm::vec3(0, 1, 0));
        rot = rot * glm::inverse(view_matrix);
    }

    ~Background() {}
};

#endif //RAYS_BACKGROUND_H
