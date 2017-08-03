#include "UI.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>
#include <iomanip>

UI::UI() {
    window = SDL_CreateWindow("Triangles",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              UI_WINDOW_WIDTH,
                              UI_WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void UI::run() {
    bool quit = false;
    SDL_Event event;
    Uint32 initial = SDL_GetTicks();
    int lastReport = 0;
    int epoc = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        int time = (SDL_GetTicks() - initial)/10000;

        population->evolve();
        epoc++;

        if (time > lastReport) {
            lastReport = time;
            std::cout << time << "\t" << epoc << "\t" << population->debug() << std::endl;
        }

        render();
    }
}

void UI::render() {
    int width = 128;
    int height = 192;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render target
    SDL_Rect targetView = { 12, 12, width, height};
    SDL_RenderCopy(renderer, targetTexture, NULL, &targetView);

    // Render best
    SDL_Rect bestView = { 24 + width, 12, width, height};
    SDL_Surface* bestSurface = population->renderBest();
    SDL_Texture* bestTexture = SDL_CreateTextureFromSurface(renderer, bestSurface);
    SDL_FreeSurface(bestSurface);
    SDL_RenderCopy(renderer, bestTexture, NULL, &bestView);
    SDL_DestroyTexture(bestTexture);

    // Render elements here
    SDL_RenderPresent(renderer);
}

void UI::setTarget(Target *target) {
    targetTexture = SDL_CreateTextureFromSurface(renderer, target->getSurface());
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
