//
// Created by maxim on 06.03.2020.
//

#ifndef FIRST_MATERIAL_H
#define FIRST_MATERIAL_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Material {
public:
    glm::vec3 diffuse_color;
    glm::vec4 albedo;
    float specular_exponent;
    float refractive_index;
    float ambient;
    Material() : diffuse_color({0, 0, 0}), albedo{1, 0, 0, 0}, specular_exponent{}, refractive_index{}, ambient{} {}

    Material(const glm::vec3 &col, const glm::vec4 &al, const float sp, const float ri, const float amb) : diffuse_color(col), albedo(al), specular_exponent(sp), refractive_index(ri), ambient(amb) {}

};

#endif //FIRST_MATERIAL_H
