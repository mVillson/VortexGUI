#pragma once

#include "..\Core.h"

#include "..\Window\Window.h"
#include "..\Window\Event.h"

#include "..\Renderer\Renderer2D.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

class VORTEX_API Gui
{
private:
	Window& mWindow;
	Event& mEvent;
public:
	Gui(Window& window, Event& event);
	void Begin();
	void End();
	void Draw();
	void Button(bool& PressState, float x, float y, float width, float height);
	static void Shutdown();
};