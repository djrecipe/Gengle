#pragma once
#ifndef __OmniCubes__
#define __OmniCubes__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "VAO.h"
#include "Buffer.h"

class Cubes : GElement
{
private:
    VAO Cubes::vao;
    Buffer Cubes::arrayBuffer;
    Buffer Cubes::elementBuffer;
public:
    static const GLuint Cubes::NumVertices = 8;
    static const GLuint Cubes::NumIndices = 6;
    GLboolean Cubes::Start(void);
};

#endif

