
#include <graphics.h>


GLuint shader_default = 0;
primitive pe_rect = {0,0,0,12,6};


void pe_init_graphics(Graphics *graphics){
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.5 context (should be core) this go into graphics init
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create the window
    graphics -> window = SDL_CreateWindow(graphics -> WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, graphics -> width, graphics -> height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (graphics -> window == NULL){
        pe_printFatalError("ERROR INITIALIZING WINDOW.", SDL_GetError());
    }
    else{
        pe_printInfo("successfully created Window", NULL);
    }

   // glad: load all OpenGL function pointers
    // ---------------------------------------
    graphics -> maincontext = SDL_GL_CreateContext(graphics -> window);
    if (graphics -> maincontext == NULL){
        pe_printFatalError("ERROR INITIALIZING OPENGL CONTEXT", SDL_GetError());
    }

    // Check OpenGL properties
    pe_printInfo("successfully loaded OpenGL Context", NULL);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        pe_printFatalError("ERROR INITIALIZING GLAD", SDL_GetError());
    }
    pe_printInfo("successfully loaded GLAD", NULL);
    pe_printNeutral("Vendor:   %s", glGetString(GL_VENDOR));
    pe_printNeutral("Renderer: %s", glGetString(GL_RENDERER));
    pe_printNeutral("Version:  %s", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, graphics -> width, graphics ->height);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    pe_init_rect(&pe_rect.VAO, &pe_rect.VBO, &pe_rect.EBO);
    shader_default = pe_CreateShaderProg("./res/shaders/Vshader.s", "./res/shaders/Fshader.s");
}

void pe_free_graphics(Graphics *graphics){
    SDL_GL_DeleteContext(graphics -> maincontext);
    pe_printInfo("renderer uninitialized",NULL);
    SDL_DestroyWindow(graphics -> window);
    pe_printInfo("window uninitialized",NULL);
}

void pe_startRender(void){
    //SDL_RenderClear(renderer);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void pe_endRender(Graphics *graphics){
    //SDL_RenderPresent(renderer);
    SDL_GL_SwapWindow(graphics->window);
}

void pe_drawCircle(float cx, float cy, float r, int num_segments)
{

}

void pe_init_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo){
    //	 x,	y, z, u, v
	float vertices[] = {
		 0.5,  0.5, 0,
		 0.5, -0.5, 0,
		-0.5, -0.5, 0,
		-0.5,  0.5, 0,
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);
	glGenBuffers(1, ebo);

	glBindVertexArray(*vao);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// xyz
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0);
}

void pe_drawRect(pe_vec2 position, pe_vec2 size, pe_vec4 color){
    /*SDL_SetRenderDrawColor(renderer, r, g ,b, a);
    SDL_RenderDrawRect(renderer, rect);*/
    pe_UseShaderProgram(shader_default);
    M4x4 model;
    M4x4_identity(model);
    M4x4_translate(model, position[0], position[1], 0);
    //scale matrix
    M4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(glGetUniformLocation(shader_default, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform4fv(glad_glGetUniformLocation(shader_default, "color"), 1, color);
    glBindVertexArray(pe_rect.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void pe_getInput(void){

}
