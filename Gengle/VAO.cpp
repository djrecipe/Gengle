#include "VAO.h"			 

#pragma region Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma endregion

#pragma region Static Members
GLuint VAO::current_index = 0;
GLuint VAO::vao[VAO::MAX_VAOS];
GLboolean VAO::occupied[VAO::MAX_VAOS] = { false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false };
#pragma endregion

#pragma region Constructors
VAO::VAO(void)
{
	this->index = -1;
	return;
}
#pragma endregion

#pragma region Initialization
GLboolean VAO::Initialize(void)
{
	GLint target_index = -1;
	for (GLint i = VAO::current_index; i < VAO::MAX_VAOS; i++)
	{
		if (!VAO::occupied[i])
		{
			target_index = i;
			break;
		}
	}
	if (target_index < 0)
	{
		for (GLint i = 0; i < VAO::current_index; i++)
		{
			if (!VAO::occupied[i])
			{
				target_index = i;
				break;
			}
		}
	}
	this->index = target_index;
	if (this->index > -1)
	{
		VAO::current_index = this->index;
		VAO::occupied[VAO::current_index] = true;
		glGenVertexArrays(1, VAO::vao + this->index);
		glBindVertexArray(VAO::vao[this->index]);
		return true;
	}
	return false;
}
#pragma endregion

#pragma region Destruction
VAO::~VAO(void)
{
	if (this->Valid())
	{
		glDeleteVertexArrays(1, &VAO::vao[this->index]);
		VAO::occupied[this->index] = false;
		this->index = -1;
	}
}
#pragma endregion

#pragma region Instance Methods
GLboolean VAO::Activate(void)
{
	if (this->Valid())
	{
		glBindVertexArray(VAO::vao[this->index]);
		return true;
	}
	return false;
}
GLboolean VAO::Valid(void)
{
	return this->index > -1;
}
#pragma endregion