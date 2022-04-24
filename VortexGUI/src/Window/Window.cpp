#include "Window.h"
#include "GLFW/glfw3.h"

struct WindowData
{
	GLFWwindow* window = nullptr;
	int width = 0;
	int height = 0;
	const char* title = "";
};

static WindowData windowData;

void windowSizeCallback(GLFWwindow* window, int width, int height);

bool Window::InitGlfw()
{
	if (!glfwInit())
		return false;
	else
		return true;
}

void Window::Shutdown()
{
	glfwTerminate();
}

void Window::CreateWindow(int width, int height, const char* title)
{
	windowData.width = width;
	windowData.height = height;
	windowData.title = title;

	windowData.window = glfwCreateWindow(windowData.width, windowData.height, windowData.title, NULL, NULL);

	glfwSetWindowSizeCallback(windowData.window, windowSizeCallback);

	glfwMakeContextCurrent(windowData.window);
}

void Window::SetTitle(const char* title)
{
	glfwSetWindowTitle(windowData.window, title);
}

void Window::SetSize(int width, int height)
{
	glfwSetWindowSize(windowData.window, width, height);
}

bool Window::GetWindowShouldClose()
{
	if (glfwWindowShouldClose(windowData.window))
		return true;
	else
		return false;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(windowData.window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}