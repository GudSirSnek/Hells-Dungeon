#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "util.h"
#include "maths.h"
#include "shader.h"
#include "graphics.h"
#include "StateManager.h"

struct EngineOptions{
  char *title;
  int width;
  int height;
};

typedef struct {
  char quit;
  Graphics *graphics;
  StateManager *statemanager;
} Engine;


void pe_Engine_init(Engine *engine, struct EngineOptions *options);

void pe_Engine_free(Engine *engine);