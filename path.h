//
// Created by tehp on 2021-04-22.
//

#ifndef TOWER_PATH_H
#define TOWER_PATH_H

#include <vector>
#include <iostream>

struct Node
{
    int y;
    int x;
    // parent
    int p_x;
    int p_y;
    // heuristics
    int f;
    float g;
    int h;
};

class Path {
public:
    Path(int sx, int sy, int ex, int ey, std::vector<std::vector<float>> m);
    ~Path();

    int g(Node n);
    int h(Node n);
    int f(Node n);

    void print_node(Node n);

    void a_star();

    std::vector<std::pair<int,int>> getPath();

private:
    int start_x, start_y;
    int end_x, end_y;
    std::vector<std::vector<float>> map;
    std::vector<std::pair<int, int>> path;
};


#endif //TOWER_PATH_H
