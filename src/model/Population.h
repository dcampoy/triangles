#ifndef TRIANGLES_POPULATION_H
#define TRIANGLES_POPULATION_H

#include "Individual.h"
#include "Target.h"
#include <list>

class Population {
public:
    Population(Target* target);
    ~Population();
    void evolve();
    SDL_Surface* renderBest();
    std::string debug();
private:
    Target* target;
    Individual* best = nullptr;
    double bestFitness;
};

#endif //TRIANGLES_POPULATION_H
