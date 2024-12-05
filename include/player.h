#ifndef PLAYER_H
#define PLAYER_H
// Include guard-> Ensures the file is compiled only once, even if the include file is included multiple times.#pragma once has the same functionality but does not work with all compilers.

#include <SDL.h>
#include "utilities.h"

#define PLAYER_INITIAL_LIVES 3
#define PLAYER_POWER_UP_TIME 5000
#define PLAYER_SPEED 2.5f
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32
#define PLAYER_ANIMATION_SPEED 10

typedef enum
{
    DIRECTION_NONE,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} player_direction_t;

typedef struct
{
    position position;
    float speed;

    float dirX; 
    float dirY;
    
    // Direzione
    player_direction_t current_direction;
    player_direction_t next_direction;

    // Stato
    int lives;             // Numero di vite rimanenti
    int score;             // Punteggio accumulato
    int is_powered_up;     // Stato "potenziato" (1 se sì, 0 altrimenti)
    Uint32 power_up_timer; // Timer per il potenziamento in millisecondi

    // Sprite e animazioni
    SDL_Texture *sprite;
    SDL_Rect frame;
    int animationSpeed;
    Uint32 lastFrameTime;
    float frame_duration;
} player_t;

void player_init(player_t *player, float x, float y, SDL_Texture *sprite);
void player_update(player_t *player, float delta_time);
void player_render(const player_t *player, SDL_Renderer *renderer);
void player_set_direction(player_t *player, player_direction_t direction);
void player_activate_power_up(player_t *player, Uint32 duration); // SDL use Uint for timers
void player_deactivate_power_up(player_t *player);
void player_reset(player_t *player, float x, float y);
int player_check_collision(const player_t *player, const SDL_Rect *other);
#endif // PLAYER_H