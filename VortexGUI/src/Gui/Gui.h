#pragma once

#include "..\Core.h"

#include "..\Window\Window.h"
#include "..\Window\Event.h"
#include "..\Renderer\Texture.h"

#include "..\Renderer\Renderer2D.h"

#include "..\..\vendor\glm\glm.hpp"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

class VORTEX_API Gui
{
private:
	Window& mWindow;
	Event& mEvent;

	unsigned int mCheckmarkTexture;
public:
	Gui(Window& window, Event& event);
	void Begin();
	void End();
	void Draw();
	void Button(bool& PressState, float x, float y, float width, float height);
	void CheckBox(bool& ToggleState, float x, float y, float size);
	void Slider(float& SliderValue, float minValue, float maxValue, float x, float y, float width, float height);
	static void Shutdown();
};