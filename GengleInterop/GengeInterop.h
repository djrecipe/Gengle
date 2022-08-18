#pragma once
#undef DestroyWindow
namespace Gengle
{
namespace Interop
{
extern "C"
{
    void ChangeSize(double width, double height);
    void CreateNewWindow(void* parent, void*& result);
    void Cleanup(void* handle);
    void Demo();
    void GetScale(double& scale_x, double& scale_y);
    void InitializeOpengl(void* hwnd);
    void Render();
}
}
}