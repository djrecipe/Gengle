#include "VoxelElement.h"
#include "Voxel.h"
#include "GlobalTools.h"
#include "ShaderConfig.h"
using namespace std;
#define FREEGLUT_STATIC

#include <glm/gtc/noise.hpp>
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

VoxelGElement::VoxelGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in) :
	GElement(shaders, vao, array_buffer_in, element_buffer_in)
{
    this->width=100;
    this->widthplus=this->width+1;
    this->widthpluscubed=this->widthplus*this->widthplus*this->widthplus;
    this->width_squared=this->width*this->width;
    this->width_cubed=this->width_squared*this->width;
    this->v_width=this->width+1;
    this->v_w_squared=this->v_width*this->v_width;
	return;
}

void VoxelGElement::Draw(void)
{
	glDrawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, (void*)0);
	return;
}

void VoxelGElement::Prepare(void)
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
void VoxelGElement::UpdateVertices()
{
    this->vox.clear();
    this->vox.reserve(this->widthpluscubed);
    for(GLuint i=0; i<this->widthpluscubed; i++)         // generate a value for each voxel
    {
        GLint z_index=i/(this->v_w_squared);                                                   // the voxel's z index
        GLint y_index=(i-z_index*(this->v_w_squared))/this->v_width;                           // the voxel's y index
        GLint x_index=(i-z_index*(this->v_w_squared)-y_index*this->v_width);                   // the voxel's x index
        //x_index+=index_offsets[0];
        //y_index+=index_offsets[1];
        //z_index+=index_offsets[2];
        //this->vox.push_back((GLchar)(glm::perlin(glm::vec3((GLfloat)x_index/130.1,(GLfloat)y_index/99.7,(GLfloat)z_index/5.2),glm::vec3(100.0f))*127.0));

        this->vox.push_back((GLchar)(glm::simplex(glm::vec3((GLdouble)x_index/79.7,(GLdouble)y_index/65.03,(GLdouble)z_index/30.261))*128.0));      // use the voxel's indices to seed a pseudo-random function
    }
    this->voxel_vec.clear();
    this->voxel_vec.reserve(width_cubed);
    //SurfaceNet my_surface;
    std::vector<glm::vec3> all_vertices;
    std::vector<GLuint> all_elements;
    for(GLuint i=0; i<width_cubed; i++)
    {
		//dprint("filling random %i", i);
        GLuint z_index=i/width_squared;
        GLuint y_index=(i-z_index*width_squared)/this->width;
        GLuint x_index=i-z_index*width_squared-y_index*this->width;
        Voxel temp_vox(this->physics.Origin[0]+(GLfloat)(x_index*this->physics.Size[0] * 2.0), this->physics.Origin[1] + (GLfloat)(y_index * this->physics.Size[1] * 2.0), this->physics.Origin[2] + (GLfloat)(z_index * this->physics.Size[2] * 2.0), this->physics.Size[0]);
        GLchar these_params[8]={this->vox[x_index+y_index*v_width+z_index*v_w_squared],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+v_w_squared],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+v_w_squared+1],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+1],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+v_width],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+v_width+v_w_squared],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+v_width+v_w_squared+1],
                                this->vox[x_index+y_index*v_width+z_index*v_w_squared+v_width+1]};
        bool limit_out[3][2]={{x_index==0,x_index>=this->width-1},{y_index==0,y_index>=this->width-1},{z_index==0,z_index>=this->width-1}};
        //bool limit_out[3][2]={{false,false},{false,false},{false,false}};
        //temp_vox.SetMarchingCubesParameters(these_params,my_surface,limit_out);
        std::vector<glm::vec3> current_vertices = temp_vox.SetMarchingCubesParameters(these_params,limit_out);
        for (int i = 0; i < current_vertices.size(); i++)
        {
            all_vertices.push_back(current_vertices[i]);
            all_elements.push_back(all_elements.size());
        }
        this->voxel_vec.push_back(temp_vox);
    }/*
	my_surface.RelaxNodes(50);
    my_surface.BlendNormals(); */
    //
    this->vertices.resize(all_vertices.size()*3);
    memcpy(&this->vertices[0], &all_vertices[0], all_vertices.size()*3 * sizeof(GLfloat));
    //
    this->elements.resize(all_elements.size());
    memcpy(&this->elements[0], &all_elements[0], all_elements.size() * sizeof(GLuint));
    return;
}