#include "Gui.h"

#include "..\..\vendor\glm\glm.hpp"
#include "..\..\vendor\glm\gtc\matrix_transform.hpp"
#include "..\..\vendor\glm\ext\matrix_projection.hpp"

Gui::Gui(Window& window, Event& event)
	:mWindow(window), mEvent(event)
{
	window.MakeContextCurrent();

	Renderer2D::Init();

	mCheckmarkTexture = Texture::LoadTexture("assets/Textures/Checkmark.png");
}

void Gui::Begin()
{
	Renderer2D::BeginBatch();
}

void Gui::End()
{
	Renderer2D::EndBatch();
}

void Gui::Draw()
{
	Renderer2D::SetModel(glm::mat4(1.0f));
	Renderer2D::SetView(glm::ortho(0.0f, (float)mWindow.GetWidth(), 0.0f, (float)mWindow.GetHeight()));
	Renderer2D::SetProjection(glm::mat4(1.0f));

	Renderer2D::Flush();
}

void Gui::Button(bool& PressState, float x, float y, float width, float height)
{
	if (mWindow.GetCursorPosX() >= x && mWindow.GetCursorPosX() <= x + width && mWindow.GetCursorPosY() >= y && mWindow.GetCursorPosY() <= y + height)
	{
		Renderer2D::DrawQuad({ x, y }, { width, height }, { 0.4f, 0.4f, 0.4f, 1.0f }); // Light Grey
		
		PressState = mEvent.IfMouseButtonPressed(MouseButton::LEFT);
	}
	else
	{
		Renderer2D::DrawQuad({ x, y}, { width, height}, { 0.3f, 0.3f, 0.3f, 1.0f }); // Darker Grey
		PressState = false;
	}
}

void Gui::CheckBox(bool& ToggleState, float x, float y, float size)
{
	static bool pressed = false;

	if (mWindow.GetCursorPosX() >= x && mWindow.GetCursorPosX() <= x + size && mWindow.GetCursorPosY() >= y && mWindow.GetCursorPosY() <= y + size)
	{
		if (mEvent.IfMouseButtonPressed(MouseButton::LEFT) && pressed == false)
		{
			ToggleState = !ToggleState;
			pressed = true;
		}
		else
		{
			if (ToggleState == false)
				Renderer2D::DrawQuad({ x, y }, { size, size }, { 0.4f, 0.4f, 0.4f, 1.0f }); // Light Grey
			if (ToggleState == true)
				Renderer2D::DrawQuad({ x, y }, { size, size }, { 0.0f, 1.0f, 0.0f, 1.0f }); // Light Green
		}
	}
	else
	{
		if (ToggleState == false)
			Renderer2D::DrawQuad({ x, y }, { size, size }, { 0.3f, 0.3f, 0.3f, 1.0f });
		else if (ToggleState == true)
			Renderer2D::DrawQuad({ x, y }, { size, size }, { 0.0f, 0.7f, 0.0f, 1.0f }); // Dark Green
	}

	if (mEvent.IfMouseButtonReleased(MouseButton::LEFT))
		pressed = false;
}

void Gui::Slider(float& SliderValue, float minValue, float maxValue, float x, float y, float width, float height)
{
	Renderer2D::DrawQuad({ x, y }, { width, height }, { 0.35f, 0.35f, 0.35f, 1.0f });
	
	static bool pressed = false;
	static float buttonWidth = width / 8;
	static float buttonX = x;

	Button(pressed, buttonX, y, buttonWidth, height);

	if (pressed)
	{
		buttonX = mWindow.GetCursorPosX() - (buttonWidth / 2);
	}

	if (buttonX < x)
		buttonX = x;
	if (buttonX > width + x - buttonWidth)
		buttonX = width + x - buttonWidth;

	SliderValue = (maxValue - minValue) / (width - buttonWidth) * (buttonX - x) + minValue;
}

void Gui::Shutdown()
{
	Renderer2D::ShutDown();

	glfwTerminate();
}