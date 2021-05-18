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

    siv::PerlinNoise perlin;

    std::srand(std::time(nullptr));
    perlin.reseed(std::rand());

    map.resize(height, std::vector<float>(width, 0.0));

    for (double y = 0; y < height; y++) {
        for (double x = 0; x < width; x++) {
            map[y][x] = perlin.accumulatedOctaveNoise2D_0_1(x/fx,y/fx,8);
        }
    }

    ax = width * ((double) std::rand() / (RAND_MAX));
    bx = width * ((double) std::rand() / (RAND_MAX));
    ay = height * ((double) std::rand() / (RAND_MAX));
    by = height * ((double) std::rand() / (RAND_MAX));

    while (map[ay][ax] < 0.28) {
        ax = width * ((double) std::rand() / (RAND_MAX));
        ay = height * ((double) std::rand() / (RAND_MAX));
    }

    while (map[by][bx] < 0.28) {
        bx = width * ((double) std::rand() / (RAND_MAX));
        by = height * ((double) std::rand() / (RAND_MAX));
    }

    std::cout << ax << "," << ay << " to -> " << bx << "," << by << std::endl;

    Path *p = new Path(ax, ay, bx, by, map);
    p->a_star();
    std::vector<std::pair<int,int>> p_path = p->getPath();
    paths.insert(paths.end(), p_path.begin(), p_path.end());
}

std::vector<std::pair<int,int>> Terrain::getPaths() {
    return paths;
}

int Terrain::getWidth() {
    return width;
}

int Terrain::getHeight() {
    return height;
}