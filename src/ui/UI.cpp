#include "UI.h"
#include <SDL_events.h>

UI::UI() {
    window = SDL_CreateWindow("Triangles",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              UI_WINDOW_WIDTH,
                              UI_WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void UI::run() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        population->evolve();

        render();
    }
}

void UI::render() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    target->render(renderer);
    population->getBest().render(renderer);

    // Render elements here
    SDL_RenderPresent(renderer);
}

void UI::setTarget(Target *target) {
    this->target = target;
}

void UI::setPopulation(Population *population) {
    this->population = population;
}

void UI::free() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    window = nullptr;
}
