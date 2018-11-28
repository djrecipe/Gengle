#include "GlutManager.h"
#include "GlobalTools.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

GLboolean GlutManager::Initialize(GLint argc, GLchar** argv,
	void (*keyboard)(unsigned char, int, int), void(*special_keyboard)(int, int, int))
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		dprint("Unable to initialize GLEW  ... exiting");
		return false;
	}
	return true;
}
