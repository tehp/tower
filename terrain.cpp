//
// Created by tehp on 2021-04-20.
//
#include <ctime>

#include "terrain.h"
#include "noise.h"

Terrain::Terrain(int w, int h, double f) {
    width = w;
    height = h;
    frequency = f;

    const double fx = width / frequency;
    const double fy = height / frequency;

    siv::PerlinNoise perlin;

    std::srand(std::time(nullptr));
    perlin.reseed(std::rand());

    map.resize(height, std::vector<float>(width, 0.0));

    for (double y = 0; y < height; y++) {
        for (double x = 0; x < width; x++) {
            map[y][x] = perlin.accumulatedOctaveNoise2D_0_1(x/fx,y/fx,8);
        }
    }
}

int Terrain::getWidth() {
    return width;
}

int Terrain::getHeight() {
    return height;
}