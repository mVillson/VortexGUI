#include "Event.h"

Event::Event(Window& window)
	:mWindow(window)
{

}

void Event::PollEvents()
{
	glfwPollEvents();
}

bool Event::IfKeyPressed(int key)
{
	if (glfwGetKey(mWindow.GetWindow(), key) == GLFW_PRESS)
		return true;
	else
		return false;
}

bool Event::IfKeyReleased(int key)
{
	if (glfwGetKey(mWindow.GetWindow(), key) == GLFW_RELEASE)
		return true;
	else
		return false;
}

bool Event::IfMouseButtonPressed(int button)
{
	if (glfwGetMouseButton(mWindow.GetWindow(), button) == GLFW_PRESS)
		return true;
	else
		return false;
}

bool Event::IfMouseButtonReleased(int button)
{
	if (glfwGetMouseButton(mWindow.GetWindow(), button) == GLFW_RELEASE)
		return true;
	else
		return false;
}