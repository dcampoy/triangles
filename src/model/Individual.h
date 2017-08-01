#ifndef TRIANGLES_INDIVIDUAL_H
#define TRIANGLES_INDIVIDUAL_H


#include <vector>
#include <random>
#include <SDL_system.h>

class Individual {
public:
    static Individual* createMonogen();
    Individual();
    ~Individual();
    Individual* reproduce(double mutationFactor);
    SDL_Surface* render();
    long complexity();
    //Individual mate(Individual partner);

private:
    struct Triangle {
        Sint16 px[3];
        Sint16 py[3];
        Uint32 color;
    };
    std::vector<Triangle> genotype;

    static Triangle generateRandomGen();

    void splitTriangle(const Triangle &t, Triangle &half1, Triangle &half2) const;
};


#endif //TRIANGLES_INDIVIDUAL_H
