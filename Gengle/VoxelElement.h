#pragma once

#include <vector>
#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "Voxel.h"
using namespace std;

class VoxelGElement : public GElement
{
private:
	vector<GLfloat> vertices;
	vector<GLuint> elements;
    GLfloat width_squared;
    GLfloat width_cubed;
    GLfloat v_width;
    GLfloat v_w_squared;
    GLuint widthplus;
    GLuint widthpluscubed;
    /// <summary>An unsigned integer representing the number of voxels in a single dimension of the voxel field (the size of each dimension should be the same). The total number of voxels will be this
    /// number to the power of three. This value is used widely through-out <c>VoxelField::FillWithRandom()</c> in order to iterate through the voxels, match corner density values to Voxel class
    /// instances, etc. <seealso cref="VoxelField::FillWithRandom()"/></summary>
    /// <remarks>This member is initialized directly via a required parameter passed to the constructor of this class.</remarks>
    GLuint width;
    /// <summary>An std::vector (managed array) of Voxel class instances which holds all of the Voxels in this entire VoxelField. This member is populated via <c>VoxelField::FillWithRandom()</c> which uses
    /// a noise function to generate a three dimensional contiguous series of corner density values which are then passed to the Voxel constructor, thus configuring the Voxel and determining its vertices.
    /// <seealso cref="VoxelField::FillWithRandom()"/><seealso cref="VoxelField::vox"/></summary>
    /// <remarks>This member need not be initialized in the constructor. Currently this member does very little outside of the scope of the original generation of the Voxels, but in the future this
    /// member will be essential to modification operations.</remarks>
    vector<Voxel> voxel_vec;
    /// <summary>An std::vector of characters (8-bit numbers) which store the corner values of all of the voxels in their original logical order, with no duplicates. Currently this member has no use
    /// outside of <c>VoxelField::FillWithRandom()</c>, but it may be used by modification operations implemented in the future.
    /// <seealso cref="VoxelField::FillWithRandom()"/><seealso cref="VoxelField::voxel_vec"/></summary>
    /// <remarks>This member need not be initialized in the constructor.</remarks>
    vector<GLchar> vox;
public:
	VoxelGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Draw(void);
	void Prepare(void);
	void UpdateVertices();
};
