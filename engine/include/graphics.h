#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "util.h"
#include "maths.h"
#include "shader.h"


extern GLuint shader_default;

typedef struct {
  int width;
  int height;
  char *WindowTitle;
  SDL_Window *window;
  SDL_GLContext *maincontext;
} Graphics;

typedef struct primitive {
  unsigned int VBO, VAO, EBO;
  int vertices;
  int indices;
} primitive;



void pe_init_graphics(Graphics *graphics);

void pe_free_graphics(Graphics *graphics);

void pe_init(void); //this is an engine func

void pe_createWindow(const char *name, int width, int height); //create window and renderer should be in the same function imo

void pe_createRenderer(void);

void pe_clearScreen(int r, int g, int b, int a);

void pe_startRender(void);

void pe_endRender(Graphics *graphics);

void pe_drawCircle(float cx, float cy, float r, int num_segments);

void pe_init_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo);

void pe_drawRect(pe_vec2 position, pe_vec2 size, pe_vec4 color);

void pe_getInput(void); //this get moved to input manager once its made

void pe_uninit(void);