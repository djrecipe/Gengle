#include "TriangleGElement.h"

#pragma region Instance Methods
/// <summary>
/// Create a new triangle using the specified resources
/// </summary>
/// <param name="shaders">Shader configuration</param>
/// <param name="vao">Vertex array</param>
/// <param name="array_buffer_in">Array buffer for vertex data</param>
TriangleGElement::TriangleGElement(ShaderConfig* shaders, VertexArray* vao, GenericBuffer* array_buffer_in)
	: GElement(shaders, vao, array_buffer_in)
{
	return;
}

/// <summary>
/// Draw the triangle
/// </summary>
/// <seealso cref="glDrawArrays"/>
void TriangleGElement::Draw(void)
{
	glDrawArrays(GL_TRIANGLES, 0, TriangleGElement::NumVertices);
	return;
}

/// <summary>
/// Prepare to draw the triangle
/// </summary>
void TriangleGElement::Prepare(void)
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
	GLfloat vertices[NumVertices][3] = {
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ -1.0f, 1.0f, 0.0f }};
	this->arrayBuffer->SendData(vertices, sizeof(vertices));
	//
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(1.0f);
	return;
}
void TriangleGElement::PrepareTexture(void)
{
    
}
#pragma endregion