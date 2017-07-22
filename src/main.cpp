#include "ui/UI.h"
#include "model/Population.h"
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>

void loadSDL();
void unloadSDL();

int main(int argc, char *argv[]) {
    Target target;
    Population population(&target);

    loadSDL();

    if (argc < 2) {
        throw std::invalid_argument("Target image required");
    }

    target.loadImage(argv[1]);

    UI ui;
    ui.setTarget(&target);
    ui.setPopulation(&population);
    ui.run();
    ui.free();
    unloadSDL();
}

void loadSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
}

void unloadSDL() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
