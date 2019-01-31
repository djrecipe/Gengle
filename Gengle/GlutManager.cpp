#include "GlutManager.h"
#include "GlobalTools.h"

GLint GlutManager::windowID = -1;

GLboolean GlutManager::Initialize(GLint argc, GLchar** argv, glm::vec2 window_size,
	void(*display_callback)(void), void(*idle_callback)(void),
	void(*keyboard_callback)(unsigned char, int, int),
	void(*keyboard_up_callback)(unsigned char, int, int),
	void(*special_keyboard_callback)(int, int, int),
	void(*mouse_move_callback)(int, int),
	void(*mouse_button_callback)(int, int, int, int))
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(window_size[0], window_size[1]);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	GlutManager::windowID = glutCreateWindow(argv[0]);
	// init callback functions
	glutDisplayFunc(display_callback);
	glutIdleFunc(idle_callback);
	glutKeyboardFunc(keyboard_callback);
	glutKeyboardUpFunc(keyboard_up_callback);
	glutSpecialFunc(special_keyboard_callback);
	glutPassiveMotionFunc(mouse_move_callback);
	glutMouseFunc(mouse_button_callback);
	//
	glutSetCursor(GLUT_CURSOR_NONE);
	glutIgnoreKeyRepeat(true);
	glewExperimental = GL_TRUE;
	glutWarpPointer(window_size[0]/2, window_size[1]/2);
	if (glewInit())
	{
		dprint("Unable to initialize GLEW  ... exiting");
		return false;
	}
	return true;
}

void GlutManager::Start(void)
{
	glutMainLoop();
	return;
}

void GlutManager::Exit(void)
{
	assert(GlutManager::windowID > -1);
	glutDestroyWindow(GlutManager::windowID);
	GlutManager::windowID = -1;
	return;
}