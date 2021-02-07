#pragma once
#include <GL/glew.h>
#include <iostream>
#include <initializer_list>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
void INFO(std::initializer_list<const char*>);