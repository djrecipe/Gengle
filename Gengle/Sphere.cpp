#include "Sphere.h"


Sphere::Sphere(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in) :
	GElement(shaders, vao, array_buffer_in, element_buffer_in)
{
	this->GenerateVertices();
	return;
}

void Sphere::Draw(void)
{
	glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, (void*)0);
	return;
}

void Sphere::Prepare(void)
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
	this->arrayBuffer->SendData(this->vertices, sizeof(this->vertices[0][0]) * this->numVertices);
	// activate element buffer
	this->elementBuffer->Activate();
	// send data to activated buffer
	this->elementBuffer->SendData(this->indices, sizeof(this->indices[0]) * this->numIndices);
	//
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(1.0f);
	return;
} 

void Sphere::GenerateVertices(void)
{
	for (GLuint i = 0; i < this->stackCount; i++)
	{
		for (GLuint j = 0; j < this->sectorCount; j++)
		{
			GLfloat x, y, z;
			this->vertices[i*j] = new GLfloat[3]{ x, y, z };
			dprint("%f,%f,%f\n", x, y, z);
		}
	}

	return;
}
 