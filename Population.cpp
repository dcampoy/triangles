#include "Population.h"

Population::Population(Target* target) {
    best = Individual::createMonogen();
    bestFitness = target->evaluateFitness(best);
}

void Population::evolve() {
    Individual* child = best->reproduce();
    double childFitness = target->evaluateFitness(child);
    if (childFitness >= bestFitness) {
        delete best;
        best = child;
        bestFitness = childFitness;
    } else {
        delete child;
    }
}

Individual Population::getBest() {
    return *best;
}

Population::~Population() {
    delete best;
}

