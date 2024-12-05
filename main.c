#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "include\player.h"

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Player Demo", 100, 100, 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player *player = CreatePlayer(renderer, "./Source/Goku.png", 100, 100, 5.0f, 50, 86);
    if (!player) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
        HandlePlayerInput(player, keyboard_state);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        RenderPlayer(renderer, player, 0, 0, 33, 0);

        SDL_RenderPresent(renderer);
    }

    DestroyPlayer(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
