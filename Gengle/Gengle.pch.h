#pragma once

#define FREEGLUT_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#define WIN32_LEAN_AND_MEAN
#define BUFFER_OFFSET(x)  ((const void*) (x))


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")
#pragma comment(lib, "FreeType/2.9.1/x32/freetype.lib")


#include <algorithm>
#include <assert.h> 
#include <combaseapi.h>
#include <chrono>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <ostream>
#include <thread>
#include <stdexcept>
#include <stack>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strsafe.h>
#include <sstream>
#include <thread>
#include <vector>
#include <windows.h>

#include <GLEW/1.11.0/glew.h>

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>

#include <Freeglut/2.8.1/VS2013/freeglut.h>
#include <FreeImage/FreeImage.h>
#ifndef FT2BUILD_H_
#define FT2BUILD_H_
#include <FreeType/2.9.1/freetype/config/ftheader.h>
#endif

