#include "UI.h"
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>

void loadSDL();
void unloadSDL();

int main(int argc, char *argv[]) {
    loadSDL();
    UI ui;
    ui.run();
    ui.free();
    unloadSDL();
}

void loadSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}

void unloadSDL() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
