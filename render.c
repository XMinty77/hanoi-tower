#include "render.h"
#include "config.h"
#include "tools.h"
#include <SDL.h>
#include <stdbool.h>

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer = NULL;

int render_count;
int **render_towers;

void render_init(int _count, int **_towers) {
    render_count = _count;
    render_towers = _towers;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        "Hanoi Tower",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void render_dispose() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render() {
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                return;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        int height = BLOCKS_HEIGHT / render_count;
        for (int i = 0; i < 3; i++) {
            int *tower = render_towers[i];
            int basex = MARGIN_X * (i + 1) + BLOCK_WIDTH * i + BLOCK_WIDTH / 2;
            int basey = MARGIN_Y;
            for (int j = 0; j < render_count; j++) {
                int block = tower[j];
                if (block == -1) continue;
                RGB_Color color = HSL_to_RGB(360.0 * block / render_count, 1.0, 0.5);
                int width = BLOCK_WIDTH * (render_count - block) / render_count;
                SDL_Rect rect = { basex - width / 2, WIN_HEIGHT - (basey + j * height), width, -height };

                double r = floor(color.R * 255.0), g = floor(color.G * 255.0), b = floor(color.B * 255.0);
                uint8_t R = (uint8_t)r, G = (uint8_t)g, B = (uint8_t)b;
                SDL_SetRenderDrawColor(renderer, R, G, B, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);

        if (DELAY != 0) SDL_Delay(DELAY);
        if (SKIP_INPUT) return;
    }
}