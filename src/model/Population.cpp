#include <iostream>
#include <sstream>
#include <iomanip>
#include "Population.h"

Population::Population(Target* target) {
    this->target = target;
}

Population::~Population() {
    delete best;
}

void Population::evolve() {
    if (best == nullptr) {
        best = Individual::createMonogen();
        bestFitness = target->evaluateFitness(best);
    } else {
        Individual *child = best->reproduce(1.0 - bestFitness);
        double childFitness = target->evaluateFitness(child);
        if (childFitness >= bestFitness) {
            delete best;
            best = child;
            bestFitness = childFitness;
        } else {
            delete child;
        }
    }
}

SDL_Surface* Population::renderBest() {
    return best->render();
}

std::string Population::debug() {
    std::stringstream stream;
    stream << std::setprecision(6) << 100*bestFitness << "\t" << best->complexity();
    return stream.str();
}
