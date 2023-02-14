#pragma once

class MathUtils
{
public:
	static glm::vec3 Normal(glm::vec3 vec0_in, glm::vec3 vec1_in, bool normalize = false);
	static GLfloat Angle(glm::vec3 vec0_in, glm::vec3 vec1_in);
};

