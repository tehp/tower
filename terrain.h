//
// Created by tehp on 2021-04-20.
//

#ifndef TOWER_TERRAIN_H
#define TOWER_TERRAIN_H

#include <vector>
#include <iostream>

#include "path.h"

class Terrain {
public:
    Terrain(int w, int h, double f);
    ~Terrain();
    int getWidth();
    int getHeight();
    std::vector<std::vector<float>> map;

    int ax, ay;
    int bx, by;

    std::vector<std::pair<int,int>> getPaths();

private:
    int width;
    int height;
    double frequency;
    std::vector<std::pair<int,int>> paths;

};
#endif //TOWER_TERRAIN_H
