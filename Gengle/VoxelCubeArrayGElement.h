#pragma once

#include <vector>
#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "Voxel.h"
using namespace std;

/// <summary>
/// A 3-dimensional array of voxel cubes which are rendered in the same call
/// </summary>
class VoxelCubeArrayGElement : public GElement
{
private:
	vector<GLfloat> vertices;
	vector<GLuint> elements;
    /// <summary>Number of voxel cubes within this voxel array</summary>
    GLuint numVoxelCubes;
public:
	VoxelCubeArrayGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Draw(void);
	void Prepare(void);
	/// <summary>
	/// Generate vertices for all voxel cubes within this array using Marching Cubes
	/// </summary>
	void GenerateVertices();
    /// <summary>
    /// Set the number of voxel cubes along a given axis. The total number of voxel cubes within the array will be this number cubed
    /// </summary>
    /// <param name="count">Number of voxel cubes along a given axis</param>
    void SetVoxelCubeCount(GLuint count);
};
