#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "terrain.h"

const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 980;

int main(int argc, char *args[]) {
    SDL_Window *window = NULL;

    SDL_Renderer* renderer = NULL;

    SDL_Surface *screenSurface = NULL;

    Terrain *t = new Terrain(SCREEN_WIDTH, SCREEN_HEIGHT, 8.0);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("tower", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {

            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            } else {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }

    bool quit = false;
    SDL_Event e;

    std::cout << "\nx: " << t->getWidth() << ", y: " << t->getHeight() << std::endl;
    
    SDL_Color color_map[t->getHeight()][t->getWidth()];

    for (int x = 0; x < (t->getWidth()); x++) {
        for (int y = 0; y < (t->getHeight()); y++) {
            double height = t->map[y][x];

            SDL_Color *color = new SDL_Color();

            if (height > 0.95) {
                // snow
                color->r = 255;
                color->g = 255;
                color->b = 255;
            } else if (height > 0.9) {
                // snow
                color->r = 240;
                color->g = 240;
                color->b = 240;
            } else if (height > 0.85) {
                // dirty snow
                color->r = 222;
                color->g = 222;
                color->b = 222;
            } else if (height > 0.8) {
                // granite
                color->r = 188;
                color->g = 188;
                color->b = 188;
            } else if (height > 0.75) {
                // rock
                color->r = 159;
                color->g = 159;
                color->b = 159;
            } else if (height > 0.7) {
                // above treeline
                color->r = 70;
                color->g = 153;
                color->b = 70;
            } else if (height > 0.6) {
                // above treeline
                color->r = 50;
                color->g = 133;
                color->b = 50;
            } else if (height > 0.5) {
                color->r = 64;
                color->g = 137;
                color->b = 70;
            } else if (height > 0.45) {
                color->r = 84;
                color->g = 157;
                color->b = 90;
            } else if (height > 0.4) {
                // grassy
                color->r = 104;
                color->g = 179;
                color->b = 105;
            } else if (height > 0.35) {
                // grassy
                color->r = 84;
                color->g = 159;
                color->b = 85;
            } else if (height > 0.28) {
                // dirt
                color->r = 194;
                color->g = 156;
                color->b = 95;
            } else if (height > 0.24) {
                // sand
                color->r = 228;
                color->g = 216;
                color->b = 149;
            } else if (height > 0.2) {
                // shallow water
                color->r = 0;
                color->g = 76;
                color->b = 151;
            } else {
                // deep water
                color->r = 0;
                color->g = 70;
                color->b = 145;
            }

            // sun
            if (y < (t->getHeight() - 1) && x < (t->getWidth() - 1)) {
                if ((t->map[y+1][x+1] - t->map[y][x]) >= 0.0075) {
                    if (t->map[y][x] > 0.24 && t->map[y][x] < 0.8) {
			int sun_mod = 24;
                        color->r += sun_mod;
                        color->g += sun_mod;
                        color->b += sun_mod;
                    }
                }
            }

            if ((abs(t->ax - x) < 5 && abs(t->ay - y) < 5) || (abs(t->bx - x) < 5 && abs(t->by - y) < 5)) {
                color->r = 255;
                color->g = 0;
                color->b = 0;
            }

	    color_map[y][x] = *color;

	}
    }

    
    for (int x = 0; x < (t->getWidth()); x++) {
        for (int y = 0; y < (t->getHeight()); y++) {

            // shadows
            if (y > 1 && x > 1) {
                if (t->map[y-1][x-1] > t->map[y][x]) {
                    if (t->map[y][x] > 0.24) {
			int shadow_mod = 40;
                        //color_map[y][x].r -= shadow_mod;
                        //color_map[y][x].g -= shadow_mod;
                        //color_map[y][x].b -= shadow_mod;
			for (int i = 0; i < 2; i++) {
				if ((x < (t->getWidth() - 20)) && (y < (t->getHeight() - 20))) {
					color_map[y+i][x+i].r -= 5;
					color_map[y+i][x+i].g -= 5;
					color_map[y+i][x+i].b -= 5;
				}
			}
                    }
                }
            }
            SDL_Rect fillRect = { x, y, 1, 1 };
            SDL_SetRenderDrawColor( renderer, color_map[y][x].r, color_map[y][x].g, color_map[y][x].b, 0xFF );
            SDL_RenderFillRect( renderer, &fillRect );
        }
    }

    std::vector<std::pair<int,int>> paths = t->getPaths();

    for(std::vector<std::pair<int,int>>::iterator it = paths.begin(); it != paths.end(); it++) {
        SDL_Rect fillRect = { it->first, it->second, 2, 2 };
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 0xFF );
        SDL_RenderFillRect( renderer, &fillRect );
    }

    SDL_RenderPresent( renderer );
    while (!quit) {
        // If any events
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
