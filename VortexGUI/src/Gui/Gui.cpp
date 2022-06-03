#include "Gui.h"

#include "..\..\vendor\glm\glm.hpp"
#include "..\..\vendor\glm\gtc\matrix_transform.hpp"
#include "..\..\vendor\glm\ext\matrix_projection.hpp"

Gui::Gui(Window& window, Event& event)
	:mWindow(window), mEvent(event)
{
	window.MakeContextCurrent();

	Renderer2D::Init();
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

}

void Gui::Shutdown()
{
	Renderer2D::ShutDown();

	glfwTerminate();
}