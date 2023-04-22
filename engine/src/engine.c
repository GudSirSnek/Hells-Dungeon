#include <engine.h>
#include <stdio.h>
#include <math.h>
static SDL_Window *window = NULL;
static SDL_GLContext maincontext;
uint32_t w_flags = 0;

void pe_init(void){
    /*
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        pe_printError("Failed to Initialize SDL: %s", SDL_GetError());
    }

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    pe_printInfo("successfully initialized Photonica Engine", NULL);
    */
   // Initialize SDL 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        pe_printError("Failed to Initialize SDL: %s", SDL_GetError());
    }

    atexit (SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    

    
}

void pe_uninit(void){
    pe_printNeutral("uninitalizing renderer, window, SDL", NULL);
    //SDL_DestroyRenderer(renderer);
    pe_printNeutral("renderer uninitialized",NULL);
    SDL_DestroyWindow(window);
    pe_printNeutral("window uninitialized",NULL);
    SDL_Quit();
    pe_printNeutral("SDL uninitialized",NULL);

    pe_printInfo("Photonica Engine successfully uninitialized",NULL);
}

void pe_createWindow(const char *title, int width, int height){
    // Create the window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window){
        pe_printFatalError("ERROR INITIALIZING WINDOW.", SDL_GetError());
    }
}


void pe_createRenderer(void){

   // glad: load all OpenGL function pointers
    // ---------------------------------------
    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == NULL){
        pe_printFatalError("ERROR INITIALIZING OPENGL CONTEXT", SDL_GetError());
    }

    // Check OpenGL properties
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void pe_clearScreen(int r, int g, int b, int a){
    //SDL_SetRenderDrawColor(renderer, r, g, b, a);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void pe_startRender(void){
    //SDL_RenderClear(renderer);
}

void pe_endRender(void){
    //SDL_RenderPresent(renderer);
    SDL_GL_SwapWindow(window);
}

void pe_drawCircle(float cx, float cy, float r, int num_segments)
{

}

void pe_drawRect(SDL_Rect* rect, int r, int g, int b, int a){
    /*SDL_SetRenderDrawColor(renderer, r, g ,b, a);
    SDL_RenderDrawRect(renderer, rect);*/
    

}

void pe_getInput(void){

}
