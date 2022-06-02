#include "Gui.h"

Gui::Gui(Window& window, Event& event)
	:mWindow(window), mEvent(event)
{
	window.MakeContextCurrent();

	Renderer2D::Init();


}

void Gui::Begin()
{

}

void Gui::End()
{

}

void Gui::Draw()
{

}

void Gui::Shutdown()
{
	Renderer2D::ShutDown();

	glfwTerminate();
}