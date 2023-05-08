#include <engine.h>
#include <stdio.h>
#include <StateManager.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FALSE 0
#define TRUE 1

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)


///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = FALSE;
int last_frame_time = 0;
const Uint8* currentKeyStates = 0;

///////////////////////////////////////////////////////////////////////////////
// Function to poll SDL events and process keyboard input
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
    
    
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    // Calculate how much we have to wait until we reach the target frame time
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    // Only delay if we are too fast too update this frame
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    // Get a delta time factor converted to seconds to be used to update my objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

    // Store the milliseconds of the current frame
    last_frame_time = SDL_GetTicks();
    //printf("\n");
}







///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    
    struct EngineOptions options = {0};
    options.title ="A window";
    options.width = 800;
    options.height = 600;
    Engine engine;
    pe_Engine_init(&engine, &options);

    SDL_Event event;
    
    pe_vec2 position = {400,300};
    pe_vec2 size = {100, 100};
    pe_vec4 color = {1,1,0,1};

    while (!engine.quit) {
       
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT){
                engine.quit = 1;
        }
        currentKeyStates = SDL_GetKeyboardState(NULL);

        if(currentKeyStates[SDL_SCANCODE_UP]){
            position[1] += 10;
        }
        if(currentKeyStates[SDL_SCANCODE_DOWN]){
            position[1] -= 10;
        }
        if(currentKeyStates[SDL_SCANCODE_LEFT]){
            position[0] -= 10;
        }
        if(currentKeyStates[SDL_SCANCODE_RIGHT]){
            position[0] += 10;
        }

        
        update();
    
        pe_startRender();
       
        pe_drawRect(position, size, color);

        pe_endRender(engine.graphics);
        //render stuff here
       
        
    }

    pe_Engine_free(&engine);

    return 0;
}
