#include <SDL_image.h>
#include <stdexcept>
#include "Target.h"

void Target::loadImage(std::string path) {
    original = IMG_Load(path.c_str());
    if (original == nullptr) {
        throw std::runtime_error(IMG_GetError());
    }
}

double Target::evaluateFitness(Individual* individual) {
    return 0.0d;
}

void Target::render(SDL_Renderer *renderer) {
    // Attempt to optimise
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, original);
    SDL_Rect rect = {12,12,original->w, original->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

