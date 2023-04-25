#pragma once

#include <glad/glad.h>



char* get_shader_content(const char* fileName);

GLuint pe_CreateShaderProg(const char* vertexShaderPath, const char* fragmentShaderPath);

void pe_UseShaderProgram(GLuint program);
