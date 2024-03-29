#pragma once

#include <GL/glew.h>
#include "DLLBuild.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void _API GLClearError();
bool _API GLLogCall(const char* function, const char* file, int line);
