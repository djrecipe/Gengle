#include "GlutManager.h"
#include "GlobalTools.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

GLboolean GlutManager::Initialize(GLint argc, GLchar** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		dprint("Unable to initialize GLEW  ... exiting");
		return false;
	}
	return true;
}
