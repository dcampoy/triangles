#include <SDL_image.h>
#include <stdexcept>
#include <cfloat>
#include "Target.h"

void Target::loadImage(std::string path) {
    original = IMG_Load(path.c_str());
    if (original == nullptr) {
        throw std::runtime_error(IMG_GetError());
    }
}

double Target::evaluateFitness(Individual* individual) {
    int width = 128;
    int height = 192;
    double total = (double)(3*128*128) * width * height;

    if (individual->complexity() == 0) {
        return -DBL_MAX;
    }

    double diff = 0 * individual->complexity();

    SDL_Surface* phenotype = individual->render();

    for (int i=0; i<(width*height); i++) {
        uint8_t pixel = 0;
        uint8_t origPixel = 0;

        // Red
        pixel = ((uint8_t*)phenotype->pixels)[4*i];
        origPixel = ((uint8_t*)original->pixels)[3*i+2];
        diff += (pixel - origPixel)*(pixel - origPixel);

        // Green
        pixel = ((uint8_t*)phenotype->pixels)[4*i+1];
        origPixel = ((uint8_t*)original->pixels)[3*i+1];
        diff += (pixel - origPixel)*(pixel - origPixel);

        // Blue
        pixel = ((uint8_t*)phenotype->pixels)[4*i+2];
        origPixel = ((uint8_t*)original->pixels)[3*i];
        diff += (pixel - origPixel)*(pixel - origPixel);
    }

    SDL_FreeSurface(phenotype);

    return 1.0d - (diff / total);
}

SDL_Surface* Target::getSurface() {
    return original;
}

