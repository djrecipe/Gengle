#include "GlutManager.h"
#include "GlobalTools.h"

GLboolean GlutManager::Initialize(GLint argc, GLchar** argv, glm::vec2 window_size,
	void (*keyboard_callback)(unsigned char, int, int),
	void(*special_keyboard_callback)(int, int, int),
	void(*mouse_move_callback)(int, int))
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(window_size[0], window_size[1]);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);
	glutKeyboardFunc(keyboard_callback);
	glutSpecialFunc(special_keyboard_callback);
	glutPassiveMotionFunc(mouse_move_callback);
	glutSetCursor(GLUT_CURSOR_NONE);
	glewExperimental = GL_TRUE;
	glutWarpPointer(window_size[0]/2, window_size[1]/2);
	if (glewInit())
	{
		dprint("Unable to initialize GLEW  ... exiting");
		return false;
	}
	return true;
}
