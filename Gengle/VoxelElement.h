#pragma once
#ifndef __OmniVoxelElement__
#define __OmniVoxelElement__
#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
class VoxelElement : GElement
{
private:
	int elementCount=0;
public:
	VoxelElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Draw(void);
	void Prepare(void);
};

#endif
