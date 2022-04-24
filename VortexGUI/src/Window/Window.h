#pragma once

#include "..\Core.h"

class VORTEX_API Window
{
public:
	static bool InitGlfw();
	static void Shutdown();

	static void CreateWindow(int width, int height, const char* title);

	static void SetTitle(const char* title);
	static void SetSize(int width, int height);

	static bool GetWindowShouldClose();
	
	static void SwapBuffers();
	static void PollEvents(); 
};