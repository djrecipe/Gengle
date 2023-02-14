#include "CubeGElement.h"
#include "GlobalTools.h"
#include "ShaderConfig.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

CubeGElement::CubeGElement(ShaderConfig* shaders, VertexArray* vao, GenericBuffer* array_buffer_in, GenericBuffer* texcoord_buffer_in, GenericBuffer* element_buffer_in) :
	GElement(shaders, vao, array_buffer_in, texcoord_buffer_in, element_buffer_in)
{
	return;
}

void CubeGElement::Draw(void)
{
	glDrawElements(GL_TRIANGLES, CubeGElement::NumIndices, GL_UNSIGNED_INT, (void*)0);
	return;
}

void CubeGElement::PrepareTexture()
{
	if (this->texture == NULL || this->textureWidth < 1 || this->textureHeight < 1)
	{
		this->shaders->GetUniform("istex")->SetValue(false);
		return;
	}
	//
	//// activate array buffer
	this->texCoordBuffer->Activate();
	//// send data to activated buffer

	GLfloat texCube[] = {
		// -Bottom- (-Z)
		//Texture
		//u    v
		0.0, 0.0, // tri1:pt1
		1.0, 0.0, // tri1:pt2 
		1.0, 1.0, // tri1:pt3
		0.0, 1.0, // tri2:pt1
		0.0, 0.0, // tri2:pt2
		0.0, 1.0, // tri2:pt3
		// -Top- (+Z)
		//Texture
		//u    v
		1.0, 1.0,
		1.0, 0.0,

	};
	//
	this->shaders->GetAttribute("vTexCoord")->Prepare();
	this->shaders->GetAttribute("vTexCoord")->Enable();
	this->texCoordBuffer->SendData(texCube, sizeof(texCube));
	//
	//glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 72, texCube);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	this->shaders->GetUniform("istex")->SetValue(this->texture != NULL);
	return;
}
void CubeGElement::Prepare(void)
{
	// configure shaders
	this->shaders->Prepare();
	// send uniform values
	this->shaders->GetUniform("modelMatrix")->SetValue(this->GetModelMatrix());
	// activate vertex array object
	this->vao->Activate();
	//
	this->shaders->GetAttribute("vPosition")->Prepare();
	this->shaders->GetAttribute("vPosition")->Enable();	
    // activate array buffer
	this->arrayBuffer->Activate();
	// send data to activated buffer
    GLfloat vertices[NumVertices][3] = {
        { -1.0f, -1.0f, -1.0f },
        { -1.0f, -1.0f,  1.0f },
        { -1.0f,  1.0f,  1.0f },
        {  1.0f,  1.0f,  1.0f },
        {  1.0f,  1.0f, -1.0f },
        {  1.0f, -1.0f, -1.0f },
        { -1.0f,  1.0f, -1.0f },
        {  1.0f, -1.0f,  1.0f } };
    this->arrayBuffer->SendData(vertices, sizeof(vertices));
    // activate element buffer
	this->elementBuffer->Activate();
	// send data to activated buffer
    GLuint indices[NumIndices] = { 0, 5, 4, 4, 6, 0, 6, 4, 3, 3, 2, 6, 2, 3, 7, 7, 1, 2, 1, 7, 5, 5, 0, 1, 0, 1, 2, 2, 6, 0, 5, 7, 3, 3, 4, 5 };
    this->elementBuffer->SendData(indices, sizeof(indices));
	this->PrepareTexture();
    //

	//glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(1.0f);
    return;
}