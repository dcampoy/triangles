#include <SDL2_gfxPrimitives.h>
#include "Individual.h"
#include <ios>

Individual::Individual() {
}

Individual* Individual::createMonogen() {
    Individual* monogen = new Individual;
    monogen->genotype.push_back(generateRandomGen());
    return monogen;
}

Individual::~Individual() {

}

Individual* Individual::reproduce(double mutationFactor) {

    double dupProb = 0.029;
    double randProb = 0.01;
    double remProb = 0.07;
    double transProb = 0.30;
    double cromaticProb = 0.30;
    double alphaProb = 0.30;

    Individual* child = new Individual;
    for (Triangle gene : genotype) {
        double mutation = (double)rand() / RAND_MAX;

        Triangle t;
        t.px[0] = gene.px[0];
        t.py[0] = gene.py[0];
        t.px[1] = gene.px[1];
        t.py[1] = gene.py[1];
        t.px[2] = gene.px[2];
        t.py[2] = gene.py[2];
        t.color = gene.color;

        if (mutation < mutationFactor) {
            mutation = (double)rand() / RAND_MAX;

            if (mutation < dupProb) {
                Individual::Triangle half1;
                Individual::Triangle half2;
                splitTriangle(t, half1, half2);
                child->genotype.push_back(half1);
                child->genotype.push_back(half2);
                continue;
            }

            mutation -= dupProb;

            if (mutation < randProb) {
                child->genotype.push_back(t);
                child->genotype.push_back(generateRandomGen());
                continue;
            }

            mutation -= randProb;

            if (mutation < remProb) {
                continue;
            }

            mutation -= remProb;

            if (mutation < transProb) {
                int changeRange = 20.0d * mutationFactor;
                if (changeRange < 3) changeRange = 3;
                int vertex = rand() % 3;
                int translationX = (rand() % (changeRange * 2 + 1)) - changeRange;
                t.px[vertex] += translationX;
                int translationY = (rand() % (changeRange * 2 + 1)) - changeRange;
                t.py[vertex] += translationY;
                child->genotype.push_back(t);
                continue;
            }

            mutation -= transProb;

            if (mutation < cromaticProb) {
                int changeRange = 20.0d * mutationFactor;
                if (changeRange < 3) changeRange = 3;
                int component = rand() % 3;
                int translation = (rand() % (changeRange * 2 + 1)) - changeRange;
                t.color += (translation << (component * 8));
                child->genotype.push_back(t);
                continue;
            }

            mutation -= cromaticProb;

            if (mutation < alphaProb) {
                int changeRange = 20.0d * mutationFactor;
                if (changeRange < 3) changeRange = 3;
                int translation = (rand() % (changeRange * 2 + 1)) - changeRange;
                t.color += (translation << 24);
                child->genotype.push_back(t);
                continue;
            }
        } else {
            child->genotype.push_back(t);
        }
    }
    return child;
}

void Individual::splitTriangle(const Individual::Triangle &t, Individual::Triangle &half1, Individual::Triangle &half2) const {
    int offset = rand() % 3;
    int i0 = (offset + 0)%3;
    int i1 = (offset + 1)%3;
    int i2 = (offset + 2)%3;
    Sint16 middlePointX = (t.px[i1] + t.px[i2])/2;
    Sint16 middlePointY = (t.py[i1] + t.py[i2])/2;
    half1.px[i0] = t.px[i0];
    half1.py[i0] = t.py[i0];
    half1.px[i1] = t.px[i1];
    half1.py[i1] = t.py[i1];
    half1.px[i2] = middlePointX;
    half1.py[i2] = middlePointY;
    half1.color = t.color;

    half2.px[i0] = t.px[i0];
    half2.py[i0] = t.py[i0];
    half2.px[i1] = middlePointX;
    half2.py[i1] = middlePointY;
    half2.px[i2] = t.px[i2];
    half2.py[i2] = t.py[i2];
    half2.color = t.color;
}

Individual::Triangle Individual::generateRandomGen() {
    Triangle t2;
    t2.px[0] = rand() % 128;
    t2.py[0] = rand() % 192;
    t2.px[1] = rand() % 128;
    t2.py[1] = rand() % 192;
    t2.px[2] = rand() % 128;
    t2.py[2] = rand() % 192;
    uint8_t alpha = (uint8_t) (rand() % 255);
    uint8_t red = (uint8_t) (rand() % 255);
    uint8_t green = (uint8_t) (rand() % 255);
    uint8_t blue = (uint8_t) (rand() % 255);
    t2.color = (alpha << 24) + (blue << 16) + (green << 8) + red;
    return t2;
}


long Individual::complexity() {
    return genotype.size();
}

SDL_Surface* Individual::render() {
    int width = 128;
    int height = 192;
    int deep = 32;

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, deep, 0,0,0,0);
    SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);


    for (Triangle triangle: genotype) {
         filledPolygonColor(renderer, triangle.px, triangle.py, 3, triangle.color);
    }

    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);


    return surface;
}

