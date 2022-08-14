//
// Created by Erhan Kurnaz on 30/05/2022.
//

#pragma once

#include "GL/glew.h"
#include "../Shader/Shader.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../VertexArray/VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
    x;                            \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void Clear() const;
    void Clear(float r, float g, float b, float a) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
