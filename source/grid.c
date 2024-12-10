#include "../include/grid.h"
#include <stdio.h>


#include <SDL.h>

char grid[GRID_HEIGHT][GRID_WIDTH];

int can_move_to_tile(int grid_x, int grid_y) {
    if (grid_x < 0 || grid_x >= GRID_WIDTH || grid_y < 0 || grid_y >= GRID_HEIGHT) {
        return 0; // Out of bounds
    }
    return grid[grid_y][grid_x] != TILE_WALL; 
}
void init_grid(char grid[GRID_HEIGHT][GRID_WIDTH]) {
    
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (x == 0 || x == GRID_WIDTH - 1 || y == 0 || y == GRID_HEIGHT - 1) {
                grid[y][x] = TILE_WALL;
            } else {
                grid[y][x] = TILE_PELLET;
            }
        }
    }
}

void update_grid(char grid[GRID_HEIGHT][GRID_WIDTH], int grid_x, int grid_y) {
    if (grid[grid_y][grid_x] == TILE_PELLET) {
        grid[grid_y][grid_x] = TILE_EMPTY; 
    }
}

void load_grid_from_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        SDL_Log("Impossibile aprire il file della griglia: %s", file_path);
        return;
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            char c = fgetc(file);
            if (c == '\n') {
                c = fgetc(file); // Salta newline
            }
            grid[y][x] = c;
        }
    }

    fclose(file);
}

void init_tile_sprites(SDL_Rect *tile_sprites) {
    tile_sprites['W'] = (SDL_Rect){0, 0, 8, 8};   // Muro
    tile_sprites['P'] = (SDL_Rect){16, 0, 8, 8};  // Pellet
    tile_sprites['U'] = (SDL_Rect){24, 0, 8, 8};  // Power-Up
    tile_sprites['E'] = (SDL_Rect){32, 0, 8, 8};  // Vuoto
}