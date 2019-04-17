#include "Cube.h"

Cube::Cube(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in) :
	GElement(shaders, vao, array_buffer_in, element_buffer_in)
{
	return;
}

void Cube::Draw(void)
{
	glDrawElements(GL_TRIANGLES, Cube::NumIndices, GL_UNSIGNED_INT, (void*)0);
	return;
}

void Cube::Prepare(void)
{
	// configure shaders
	this->shaders->Prepare();
	// send uniform values
	this->shaders->GetUniform("modelMatrix")->SetValue(this->GetModelMatrix());
	this->shaders->GetUniform("inputColor")->SetValue(glm::vec4(0.05, 0.1, 0.9, 1.0));
	// activate vertex array object
	this->vao->Activate();
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
    //
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(1.0f);
    return;
}