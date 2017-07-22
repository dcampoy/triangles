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
    Individual* reproduce();
    void render(SDL_Renderer* renderer);
    //Individual mate(Individual partner);

private:
    struct Triangle {
        Sint16 px[3];
        Sint16 py[3];
        Uint32 color;
    };
    std::vector<Triangle> genotype;


};


#endif //TRIANGLES_INDIVIDUAL_H
