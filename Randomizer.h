//
// Created by maxim on 16.03.2020.
//

#ifndef RAYS_RANDOMIZER_H
#define RAYS_RANDOMIZER_H

#include <random>

class Randomizer {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
public:
    Randomizer() : distribution(0.0, 1.0) {};

    float get_random() {
        return distribution(generator);
    }
};

#endif //RAYS_RANDOMIZER_H
