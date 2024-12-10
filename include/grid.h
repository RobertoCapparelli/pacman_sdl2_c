#ifndef GRID_H
#define GRID_H

#define GRID_WIDTH 28
#define GRID_HEIGHT 36
#define TILE_SIZE 8 

// Tile types
#define TILE_WALL 'W'
#define TILE_PELLET 'P'
#define TILE_EMPTY 'E'
#define TILE_GHOST 'G'
#define TILE_POWERUP 'U'

int can_move_to_tile(int grid_x, int grid_y);
void init_grid(char grid[GRID_HEIGHT][GRID_WIDTH]);
void update_grid(char grid[GRID_HEIGHT][GRID_WIDTH], int grid_x, int grid_y);
void load_grid_from_file(const char *file_path);
void init_tile_sprites(SDL_Rect *tile_sprites);

extern char grid[GRID_HEIGHT][GRID_WIDTH];

#endif // GRID_H