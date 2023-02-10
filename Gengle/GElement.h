#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GenericBuffer.h"
#include "PhysicsDescriptor.h"
#include "ShaderConfig.h"
#include "VertexArray.h"

enum RotationOrders : GLuint { RotationOrderOne = 0, RotationOrderTwo = 1 };

class GElement
{
protected:
	GUID id;

	PhysicsDescriptor physics;
	GLboolean enablePhysics = true;

	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 rotationAxisOne = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 rotationAxisTwo = glm::vec3(1.0f, 0.0f, 0.0f);
	GLfloat rotationAngleOne = 0.0f;
	GLfloat rotationAngleTwo = 0.0f;

	VertexArray* vao;
	GenericBuffer* arrayBuffer = NULL;
	GenericBuffer* texCoordBuffer = NULL;
	GenericBuffer* elementBuffer = NULL;
	ShaderConfig* shaders;

	GLuint textureId;
	FIBITMAP * texture = NULL;
	GLint textureWidth = 0;
	GLint textureHeight = 0;

	void UpdatePhysicsHitbox(void);
public:
	GElement(ShaderConfig* shaders_in, VertexArray* vao_in);
	GElement(ShaderConfig* shaders_in, VertexArray* vao_in, GenericBuffer* array_buffer_in);
	GElement(ShaderConfig* shaders_in, VertexArray* vao_in, GenericBuffer* array_buffer_in, GenericBuffer* texcoord_buffer_in, GenericBuffer* element_buffer_in);

	~GElement();

	void ConsumePhysicsDescriptor(PhysicsDescriptor descriptor);
	virtual void Draw(void) = 0;
	virtual void Prepare(void) = 0;
	void PrepareHitbox(void);
	virtual void PrepareTexture() = 0;
	GLboolean GetDrawHitbox(void);
	GLboolean GetEnablePhysics(void);
	GUID GetID(void);
	glm::mat4x4 GetModelMatrix(void)
	{
		glm::mat4x4 matrix(1.0);
		matrix = glm::translate(matrix, this->physics.Origin);
		matrix = glm::rotate(matrix, this->rotationAngleOne, this->rotationAxisOne);
		matrix = glm::rotate(matrix, this->rotationAngleTwo, this->rotationAxisTwo);
		matrix = glm::scale(matrix, this->scale);
		return matrix;
	}
	PhysicsDescriptor GetPhysicsDescriptor(void);

	void SetAcceleration(glm::vec3 value);
	void SetEnablePhysics(GLboolean value);
	void SetOrigin(glm::vec3 value)
	{
		this->physics.Origin = value;
		return;
	}
	void SetRotation(GLfloat angle, glm::vec3 axis, RotationOrders rotation_order = RotationOrderOne)
	{
		switch (rotation_order)
		{
		case RotationOrderOne:
			this->rotationAngleOne = angle;
			this->rotationAxisOne = axis;
			break;
		case RotationOrderTwo:
			this->rotationAngleTwo = angle;
			this->rotationAxisTwo = axis;
			break;
		}
		this->UpdatePhysicsHitbox();
		return;
	}
	void SetScale(glm::vec3 value)
	{
		this->scale = value;
		this->UpdatePhysicsHitbox();
		return;
	}

	void SetTexture(GLchar* path)
	{
		if (this->texture != NULL)
			FreeImage_Unload(this->texture);
		
		FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(path, 0), path);
		this->texture = FreeImage_ConvertTo32Bits(bitmap);
		this->textureWidth = FreeImage_GetWidth(this->texture);
		this->textureHeight = FreeImage_GetHeight(this->texture);
		dprint("Texture '%s' is %d x %d\n", path, this->textureWidth, this->textureHeight);
		glGenTextures(1, &this->textureId);
		glBindTexture(GL_TEXTURE_2D, this->textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->textureWidth, this->textureHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(this->texture));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		return;
	}

	void SetVelocity(glm::vec3 value);
};

