#include "AxisGElement.h"

#pragma region Instance Methods
AxisGElement::AxisGElement() : GElement()
{
    
}
/// <summary>
/// Create a new triangle using the specified resources
/// </summary>
/// <param name="shaders">Shader configuration</param>
/// <param name="vao">Vertex array</param>
/// <param name="array_buffer_in">Array buffer for vertex data</param>
AxisGElement::AxisGElement(ShaderConfig* shaders, VertexArray* vao, GenericBuffer* array_buffer_in)
	: GElement(shaders, vao, array_buffer_in)
{
	return;
}

/// <summary>
/// Draw the triangle
/// </summary>
/// <seealso cref="glDrawArrays"/>
void AxisGElement::Draw(void)
{
	glDrawElements(GL_LINES, AxisGElement::NumIndices, GL_UNSIGNED_INT, (void*)0);
	return;
}

/// <summary>
/// Prepare to draw the triangle
/// </summary>
void AxisGElement::Prepare(void)
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
		{ 1.0f, -1.0f, 0.0f }
	};
	this->arrayBuffer->SendData(vertices, sizeof(vertices));
	// activate element buffer
	this->elementBuffer->Activate();
	// send data to activated buffer
	GLuint indices[NumIndices] = { 0, 1 };
	this->elementBuffer->SendData(indices, sizeof(indices));
	//
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(5.0f);
	return;
}
#pragma endregion