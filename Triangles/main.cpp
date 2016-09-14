#include <iostream>
using namespace std;

#define FREEGLUT_STATIC

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>
#include <Freeglut/2.8.1/VS2013/freeglut.h>	

#include "GlobalTools.h"    
#include "Cubes.h"
#include "Triangles.h"
#include "GlutManager.h"
		

int main(int argc, char** argv)
{
	if (!GlutManager::Initialize(argc, argv))
		return -1;
	//Triangles triangles = Triangles();
	//triangles.Start();
    Cubes cubes = Cubes();
    cubes.Start();
	return 0;
}

