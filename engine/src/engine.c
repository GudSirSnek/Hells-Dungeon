#include <engine.h>

void pe_Engine_init(Engine *engine, struct EngineOptions *options){

    //init sdl
    // Initialize SDL 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        pe_printError("Failed to Initialize SDL: %s", SDL_GetError());
    }
    pe_printInfo("successfully initialized SDL2", NULL);

    //init graphics
    engine->graphics->WindowTitle = options->title;
    engine->graphics->width = options->width;
    engine->graphics->height = options->height;
    pe_init_graphics(engine->graphics);

    engine->quit = 0;
    //init statemanager
    //init input manager

}

void pe_Engine_free(Engine *engine){

    //free input manager
    //free statemanager
    pe_printInfo("uninitalizing renderer, window, SDL", NULL);
    pe_free_graphics(engine->graphics);
    pe_printInfo("renderer uninitialized",NULL);
    SDL_Quit();
    pe_printInfo("SDL2 uninitialized",NULL);

    pe_printInfo("Photonica Engine successfully uninitialized",NULL);

}
