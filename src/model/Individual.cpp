#include <SDL2_gfxPrimitives.h>
#include "Individual.h"
#include <ios>

Individual::Individual() {
}

Individual* Individual::createMonogen() {
    Individual* monogen = new Individual;

    Triangle initial;
    initial.px[0] = rand()%128;
    initial.py[0] = rand()%192;
    initial.px[1] = rand()%128;
    initial.py[1] = rand()%192;
    initial.px[2] = rand()%128;
    initial.py[2] = rand()%192;
    initial.color = 0xFF888888;

    monogen->genotype.push_back(initial);

    return monogen;
}

Individual::~Individual() {

}

Individual* Individual::reproduce() {

    Individual* child = new Individual;
    Triangle t;
    child->genotype = genotype;
    t.px[0] = rand()%128;
    t.py[0] = rand()%192;
    t.px[1] = rand()%128;
    t.py[1] = rand()%192;
    t.px[2] = rand()%128;
    t.py[2] = rand()%192;
    uint8_t gray = (uint8_t) (rand() % 255);

    t.color = 0x11000000 + (gray << 16) + (gray << 8) + gray;
    child->genotype.push_back(t);
    return child;
}



void Individual::render(SDL_Renderer *renderer) {
    int width = 128;
    int height = 192;

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height );
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
    SDL_RenderClear(renderer);

    for (Triangle triangle: genotype) {
        filledPolygonColor(renderer, triangle.px, triangle.py, 3, triangle.color);
    }
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Rect rect = {152,12, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect );
    SDL_DestroyTexture(texture);
}

