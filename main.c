#include "render.h"
#include "audio.h"
#include "tools.h"
#include "solve.h"
#include "config.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

int skipping = 0;
void update() {
    if (skipping == 0) render();
    skipping = (skipping + 1) % SKIPPING;
    audio_play();
}

int main(int argc, char* argv[]) {
    int count;
    printf("Please enter the number of disks: ");
    scanf("%d", &count);

    int **towers = solve_init(count);
    render_init(count, towers);
    audio_init();

    solve(count, A, C, update);

    update(towers);
    SDL_Delay(2000);

    audio_dispose();
    render_dispose();
    solve_dispose();

    return 0;
}