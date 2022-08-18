#pragma once
namespace Gengle
{
    namespace Interop
    {
        extern "C"
        {
            void CreateNewWindow(void* parent, void*& result);
            void Demo();
        }
    }
}