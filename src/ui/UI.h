#ifndef TRIANGLES_UI_H
#define TRIANGLES_UI_H

#include <SDL_video.h>
#include <SDL_system.h>
#include "../model/Target.h"
#include "../model/Population.h"

const int UI_WINDOW_WIDTH = 640;
const int UI_WINDOW_HEIGHT = 480;

class UI {

public:
    UI();
    void run();
    void free();
    void setTarget(Target* target);
    void setPopulation(Population* population);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* targetTexture;
    Population* population;
    void render();
};


#endif //TRIANGLES_UI_H
