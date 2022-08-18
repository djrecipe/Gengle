#pragma once
#include <iostream>
#include <vector>

#include "WindowManager.h"
using namespace std;

#define FREEGLUT_STATIC

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>

#include "GlobalTools.h"    
#include "CubeGElement.h"
#include "TriangleGElement.h"
#include "GengleEngine.h"
#include "GlutManager.h"
#include "VoxelCubeArrayGElement.h"
namespace Gengle
{
    namespace Interop
    {
        extern "C"
        {
			void CreateNewWindow(void* hwndParent, void*& result)
			{
				HINSTANCE m_hInstance = (HINSTANCE)GetModuleHandle(NULL);
				wstring m_sWindowName = L"OpenGL in HwndHost";
				wstring m_sClassName = L"OGLClassHwnd";
				DWORD dwStyle = WS_CHILD | WS_VISIBLE;
				int iWidth = 2;
				int iHeight = 2;
				HWND parentHwnd = (HWND)hwndParent;
				HWND m_hWnd = CreateWindowEx(0,
					m_sClassName.c_str(),
					m_sWindowName.c_str(),
					dwStyle,
					0,  // X Pos
					0,  // Y Pos
					iWidth,
					iHeight,
					parentHwnd, // Parent
					0,  // Menu
					m_hInstance,
					0); // Param
				result = m_hWnd;
			}
            void Demo(void)
            {
				glm::vec2 window_size = glm::vec2(1600, 900);
				// create engine
				char* args[] = {(char*)" "};
				GengleEngine engine(0, args, window_size);
				// define elements
				GElement* element = NULL;
				element = engine.AddBasicElement(CubeElement);
				element->SetScale(glm::vec3(10.0, 10.0, 10.0));
				element->SetRotation(glm::radians(70.0f), glm::vec3(0.0, 1.0, 1.0));
				element->SetOrigin(glm::vec3(10.0, -10.0, 0.0));
				element->SetTexture((GLchar*)"BoxTexture.jpg");
				//
				VoxelCubeArrayGElement* voxel_element = (VoxelCubeArrayGElement*)engine.AddBasicElement(VoxelElement);
				voxel_element->SetOrigin(glm::vec3(0.0, 0.0, 0.0));
				voxel_element->SetScale(glm::vec3(4.0, 4.0, 4.0));
				voxel_element->SetVoxelCubeCount(40);
				voxel_element->GenerateVertices();
				// start display loop
				engine.Start();
            }
        }
    }
}