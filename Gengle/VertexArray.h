#pragma once	

#ifndef __OmniVertexArray__
#define __OmniVertexArray__

/// <summary>
/// Vertex array descriptor and function wrapper
/// </summary>
class VertexArray
{
private:
	static const GLuint MAX_VAOS = 64;
	static GLuint current_index;
	static GLuint vao[VertexArray::MAX_VAOS];
	static GLboolean occupied[VertexArray::MAX_VAOS];
	GLint index;
public:
	void Activate(void);
	void Delete(void);
	void Initialize(void);
	GLboolean Valid(void);
	VertexArray();
	~VertexArray();
};

#endif // __OmniVertexArray__