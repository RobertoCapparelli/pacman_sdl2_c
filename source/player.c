#include "../include/player.h"
#include "../stb_image.h"

#include <stdio.h>

void player_init(player_t *player, float x, float y, SDL_Texture *sprite)
{
    if (player == NULL || sprite == NULL)
    {
        SDL_Log("player_init: Player or sprite is NULL!");
        return;
    }

    player->position.x = x;
    player->position.y = y;
    player->position.renderX = (int)x;
    player->position.renderY = (int)y;

    player->speed = PLAYER_SPEED;

    player->current_direction = DIRECTION_NONE;
    player->next_direction = DIRECTION_NONE;

    player->lives = PLAYER_INITIAL_LIVES;
    player->score = 0;
    player->is_powered_up = 0;
    player->power_up_timer = 0;

    player->sprite = sprite;
    player->frame.x = 0;
    player->frame.y = 0;
    player->frame.w = PLAYER_WIDTH;
    player->frame.h = PLAYER_HEIGHT;
    player->animationSpeed = PLAYER_ANIMATION_SPEED;
    player->lastFrameTime = SDL_GetPerformanceCounter();

    float frame_duration = 1.0f / PLAYER_ANIMATION_SPEED;

    SDL_Log("Player initialized at position (%f, %f) with %d lives.", x, y, PLAYER_INITIAL_LIVES);
}

void player_update(player_t *player, float delta_time)
{
    if (!player)
        return;

    player->position.x += player->speed * player->dirX * delta_time;
    player->position.y += player->speed * player->dirY * delta_time;

    player->lastFrameTime += delta_time;

    if (player->lastFrameTime >= frame_duration)
    {
        // Next frame
        player->frame.x += PLAYER_WIDTH;
        if (player->frame.x >= player->sprite->w)
        {
            player->frame.x = 0;
        }
        player->lastFrameTime -= frame_duration;
    }
}

void player_set_direction(player_t *player, player_direction_t direction)
{
    if (!player)
        return;

    player->current_direction = direction;

    switch (direction)
    {
    case DIRECTION_UP:
        player->dirX = 0;
        player->dirY = -1;
        break;
    case DIRECTION_DOWN:
        player->dirX = 0;
        player->dirY = 1;
        break;
    case DIRECTION_LEFT:
        player->dirX = -1;
        player->dirY = 0;
        break;
    case DIRECTION_RIGHT:
        player->dirX = 1;
        player->dirY = 0;
        break;
    case DIRECTION_NONE:
    default:
        player->dirX = 0;
        player->dirY = 0;
        break;
    }
}


void player_render(const player_t *player, SDL_Renderer *renderer) {
    if (!player || !renderer || !player->sprite) {
        SDL_Log("player_render: player, renderer or sprite null!");
        return;
    }

    SDL_Rect dest_rect = {
        player->position.renderX,
        player->position.renderY,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    };

    //Current frame
    if (SDL_RenderCopy(renderer, player->sprite, &player->frame, &dest_rect) != 0) {
        SDL_Log("player_render: impossible draw player: %s", SDL_GetError());
    }
}
