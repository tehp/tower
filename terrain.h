//
// Created by tehp on 2021-04-20.
//

#ifndef TOWER_TERRAIN_H
#define TOWER_TERRAIN_H

#include <vector>
#include <iostream>

class Terrain {
public:
    Terrain(int w, int h, double f);
    ~Terrain();
    int getWidth();
    int getHeight();
    std::vector<std::vector<float>> map;

private:
    int width;
    int height;
    double frequency;


};
#endif //TOWER_TERRAIN_H
