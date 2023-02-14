#pragma once

struct PhysicsRectangle
{
private:
	glm::vec3 origin;
	glm::vec3 scale;
public:
	PhysicsRectangle(glm::vec3 origin_in, glm::vec3 scale_in);
	~PhysicsRectangle();

	GLfloat GetXMax(void);
	GLfloat GetXMin(void);
	GLfloat GetYMax(void);
	GLfloat GetYMin(void);
	GLfloat GetZMax(void);
	GLfloat GetZMin(void);
	GLboolean Intersects(PhysicsRectangle target);
};

