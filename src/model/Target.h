#ifndef TRIANGLES_TARGET_H
#define TRIANGLES_TARGET_H

#include <SDL_system.h>
#include <string>
#include "Individual.h"

class Target {
public:
    void loadImage(std::string path);
    double evaluateFitness(Individual* individual);
    SDL_Surface* getSurface();
private:
    SDL_Surface* original = nullptr;
};


#endif //TRIANGLES_TARGET_H
