#include "Gengle.pch.h"
#include "MathUtils.h"


glm::vec3 MathUtils::Normal(glm::vec3 vec0_in, glm::vec3 vec1_in, bool normalize)
{
	glm::vec3 retval = glm::cross(vec0_in, vec1_in);
	return (normalize && glm::length(retval) > 0.0) ? retval / glm::length(retval) : retval;
}
GLfloat MathUtils::Angle(glm::vec3 vec0_in, glm::vec3 vec1_in)
{
	return glm::degrees(glm::acos(glm::dot(vec0_in, vec1_in) / (glm::length(vec0_in) * glm::length(vec1_in))));
}