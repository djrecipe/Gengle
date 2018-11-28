#include "ShaderUniform.h"



ShaderUniform::ShaderUniform(const char * name_in, GLenum type_in)
{
	this->name = name_in;
	this->type = type_in;
	return;
}

ShaderUniform::~ShaderUniform()
{
}
