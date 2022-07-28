#include "VoxelCubeArrayGElement.h"
#include "Voxel.h"
#include "GlobalTools.h"
#include "MathUtils.h"
#include "ShaderConfig.h"
using namespace std;
#define FREEGLUT_STATIC

#include <glm/gtc/noise.hpp>
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

VoxelCubeArrayGElement::VoxelCubeArrayGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in) :
	GElement(shaders, vao, array_buffer_in, element_buffer_in)
{
    this->numVoxelCubes=10;
	return;
}

void VoxelCubeArrayGElement::Draw(void)
{
	glDrawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, (void*)0);
	return;
}

void VoxelCubeArrayGElement::Prepare(void)
{
	// configure shaders
	this->shaders->Prepare();
	// send uniform values
	this->shaders->GetUniform("modelMatrix")->SetValue(this->GetModelMatrix());
	// activate vertex array object
	this->vao->Activate();
    // activate array buffer
	this->arrayBuffer->Activate();
	// send data to activated buffer
    this->arrayBuffer->SendData(&vertices[0], vertices.size() * sizeof(GLfloat));
    // activate element buffer
	this->elementBuffer->Activate();
	// send data to activated buffer
    this->elementBuffer->SendData(&elements[0], elements.size() * sizeof(GLuint));
	this->PrepareTexture();
    //
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(1.0f);
    return;
}
void VoxelCubeArrayGElement::SetVoxelCubeCount(GLuint count)
{
    this->numVoxelCubes = count;
    return;
}
void VoxelCubeArrayGElement::GenerateVertices()
{
    // calculate various squares
    GLuint width_squared=this->numVoxelCubes*this->numVoxelCubes;
    GLuint width_cubed=width_squared*this->numVoxelCubes;
    GLuint v_width=this->numVoxelCubes+1;
    GLuint v_w_squared=v_width*v_width;
    // scale should be equal on all axes
    //assert(this->physics.Size[0] == this->physics.Size[1] == this->physics.Size[2]);
    // determine voxel count
    unsigned int voxel_count = pow(this->numVoxelCubes+1, 3);
    // create voxel values
    vector<GLuint> voxels;
    for(GLuint i=0; i<voxel_count; i++)         // generate a value for each voxel
    {
        GLint z_index=i/v_w_squared;                                                   // the voxel's z index
        GLint y_index=(i-z_index*v_w_squared)/v_width;                           // the voxel's y index
        GLint x_index=(i-z_index*(v_w_squared)-y_index*v_width);                   // the voxel's x index
        //this->vox.push_back((GLchar)(glm::perlin(glm::vec3((GLfloat)x_index/130.1,(GLfloat)y_index/99.7,(GLfloat)z_index/5.2),glm::vec3(100.0f))*127.0));
        /* the divisors here determine how chaotic the voxel values are: if the voxel values are too chaotic, mesh quality will suffer (jagged edges, etc.)*/
        voxels.push_back((GLchar)(glm::simplex(glm::vec3((GLdouble)x_index/79.7,(GLdouble)y_index/65.03,(GLdouble)z_index/30.261))*128.0));      // use the voxel's indices to seed a pseudo-random function
    }
    //SurfaceNet my_surface;
    std::vector<glm::vec3> all_vertices;
    std::vector<glm::vec3> all_normals;
    std::vector<GLuint> all_elements;
    for(GLuint i=0; i<width_cubed; i++)
    {
		//dprint("filling random %i", i);
        GLuint z_index=i/width_squared;
        GLuint y_index=(i-z_index*width_squared)/this->numVoxelCubes;
        GLuint x_index=i-z_index*width_squared-y_index*this->numVoxelCubes;
        Voxel temp_vox(this->physics.Origin[0]+(GLfloat)(x_index*this->physics.Size[0] * 2.0), this->physics.Origin[1] + (GLfloat)(y_index * this->physics.Size[1] * 2.0), this->physics.Origin[2] + (GLfloat)(z_index * this->physics.Size[2] * 2.0), this->physics.Size[0]);
        GLchar these_params[8]={voxels[x_index+y_index*v_width+z_index*v_w_squared],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+v_w_squared],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+v_w_squared+1],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+1],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+v_width],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+v_width+v_w_squared],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+v_width+v_w_squared+1],
                                voxels[x_index+y_index*v_width+z_index*v_w_squared+v_width+1]};
        std::vector<glm::vec3> current_vertices = temp_vox.SetMarchingCubesParameters(these_params);
        for (int i = 0; i < current_vertices.size(); i++)
        {
            all_vertices.push_back(current_vertices[i]);
            all_elements.push_back(all_elements.size());
        }
    }
    // calculate normals
    GLuint these_indices[3];
    for (GLuint i = 0; i < all_elements.size(); i++)
    {
        these_indices[i % 3] = all_elements[i];
        if (i % 3 == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                glm::vec3 normal = MathUtils::Normal(
                    all_vertices[these_indices[1]] - all_vertices[these_indices[0]],
                    all_vertices[these_indices[2]] - all_vertices[these_indices[0]],
                    false);
                all_normals.push_back(normal);
            }
        }
    }
    // copy vertices
    this->vertices.resize(all_vertices.size()*3);
    memcpy(&this->vertices[0], &all_vertices[0], all_vertices.size()*3 * sizeof(GLfloat));
    // copy element indices
    this->elements.resize(all_elements.size());
    memcpy(&this->elements[0], &all_elements[0], all_elements.size() * sizeof(GLuint));
    // copy normals
    this->normals.resize(all_normals.size());
    memcpy(&this->normals[0], &all_normals[0], all_normals.size() * sizeof(GLfloat));
    return;
}