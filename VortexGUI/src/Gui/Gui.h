#pragma once

#include "..\Core.h"

#include "..\Window\Window.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

class VORTEX_API Gui
{
private:
public:
	Gui(Window& window);
	static void Shutdown();
};