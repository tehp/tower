//
// Created by tehp on 2021-04-22.
//

#include <math.h>
#include <list>
#include <cfloat>
#include <array>
#include <stack>
#include <map>
#include <unistd.h>

#include "path.h"

#define X_MAX 2000
#define X_STEP 1
#define Y_MAX 2000
#define Y_STEP 1

using namespace std;

Path::Path(int sx, int sy, int ex, int ey, std::vector<std::vector<float>> m) {
    start_x = sx;
    start_y = sy;
    end_x = ex;
    end_y = ey;
    map = m;
}

// cost to here (should be set within code)
int Path::g(Node n) {
    return n.g;
}
 // estimated cost to destination
int Path::h(Node n) {
    return  sqrt( abs(n.x - end_x) + abs(n.y - end_y) );
}

int Path::f(Node n) {
    return (g(n) + h(n));
}

void Path::print_node(Node n) {
    std::cout << "x:" << n.x << " y:" << n.y << " f:" << n.f << " g:" << n.g << " h:" << n.h << std::endl;
}

std::vector<std::pair<int,int>> Path::getPath() {
    return path;
}

void print_progress_bar(double progress) {
	int progress_round = (int)(progress * 100);
	std::cout << "\rFinding suitable paths: " << progress_round << "%";
}

void Path::a_star() {
    std::cout << "Creating path. Method: A*" << std::endl;

    // visited but not expanded
    std::vector<Node> open;

    // visited and expanded
    std::vector<Node> closed;

    std::map<std::pair<int,int>,std::pair<int,int>> parents;

    Node start;
    start.x = start_x;
    start.y = start_y;
    start.f = h(start);
    start.g = 0;

    open.push_back(start);

    int init_dist_x = std::abs(start_x - end_x);
    int init_dist_y = std::abs(start_y - end_y);
    int init_dist_sum = init_dist_x + init_dist_y;

    std::cout << std::endl;

    while (open.size() > 0) {
        sort(open.begin(), open.end(), [](const Node& lhs, const Node& rhs) {
            return lhs.f > rhs.f;
        });

        Node current = open.back();
        open.pop_back();
        closed.push_back(current);
	
	int dist_x = std::abs(current.x - end_x);
	int dist_y = std::abs(current.y - end_y);
	int dist_sum = dist_x + dist_y;

	int dist_progress = init_dist_sum - dist_sum;
	double progress_percent = 1.0-((double)dist_sum / (double)init_dist_sum);

	print_progress_bar(progress_percent);

        // if done
        if (current.x == end_x && current.y == end_y) {            
            std::pair<int,int> c(current.x, current.y);
            std::pair<int,int> p;

            while (c.first != start_x || c.second != start_y) {
                p = parents[c];
                c = p;
                path.push_back(std::pair<int,int> (c.first, c.second));
            }

            break;
        }

        // look at neighbors
        Node n = current;
        Node s = current;
        Node e = current;
        Node w = current;

        int step = 1;
        n.y = n.y + step;
        s.y = s.y - step;
        e.x = e.x + step;
        w.x = w.x - step;

        std::vector<Node> current_neighbors;
        current_neighbors.push_back(n);
        current_neighbors.push_back(s);
        current_neighbors.push_back(e);
        current_neighbors.push_back(w);
        
        for(std::vector<Node>::iterator it = current_neighbors.begin(); it != current_neighbors.end(); it++) {
            
            if (map[it->y][it->x] < 0.28) {
                continue;
            }

            bool neighbor_in_open = false;
            bool neighbor_in_closed = false;

            for(std::vector<Node>::iterator closed_it = closed.begin(); closed_it != closed.end(); closed_it++) {
                    if (closed_it->x == it->x && closed_it->y == it->y) {
                        neighbor_in_closed = true;
                    }
            }

            for(std::vector<Node>::iterator open_it = open.begin(); open_it != open.end(); open_it++) {
                    if (open_it->x == it->x && open_it->y == it->y) {
                        neighbor_in_open = true;
                    }
            }

            if (neighbor_in_closed){
                continue;
            }

            std::map<std::pair<int,int>,std::pair<int,int>>::iterator search;
            
            float height = map[it->y][it->x];
            height += current.g;

            it->g = current.g + height; // TODO: add height
            
            it->f = f(*it);
            it->h = h(*it);
            std::pair<int,int> p(it->x,it->y);
            std::pair<int,int> c(current.x,current.y);

            if (neighbor_in_open) {
                for(std::vector<Node>::iterator open_it = open.begin(); open_it != open.end(); open_it++) {
                    if (open_it->x == it->x && open_it->y == it->y) {
                        if(open_it->g > it->g) {
                            open_it->g = it->g;

                            std::pair<int,int> o(open_it->x,open_it->y);
                            std::pair<int,int> i(it->x,it->y);

                            if (o != i) {
                                parents[o] = i;
                            }

                            open_it->h = h(*open_it);
                            open_it->f = f(*open_it);

                            continue;
                        }
                    }
                }
            } else {
                open.push_back(*it);
                if (p != c) {
                    parents[p] = c;
                }
            }
        }
    }
}
