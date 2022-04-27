#include "Window.h"
#include "GLFW/glfw3.h"

bool InitGlfw()
{
	if (!glfwInit())
		return false;
	else
		return true;
}

void ShutdownGlfw()
{
	glfwTerminate();
}

struct WindowData
{
	static const int windowMaxCount = 16;
	int id;
	GLFWwindow* window[windowMaxCount];
	WindowData() 
	{
		id = 0;
		for (int i = 0; i < windowMaxCount; i++)
		{
			window[i] = nullptr;
		}
	}
};

WindowData windowData;

void windowSizeCallback(GLFWwindow* window, int width, int height);

Window::Window()
	:mWidth(0), mHeight(0), mTitle(""), mVSync(false), mCreated(false)
{

}

Window::Window(int width, int height, const char* title)
{
	mWindowID = windowData.id;
	windowData.id++;

	mWidth = width;
	mHeight = height;
	mTitle = title;
	mVSync = false;

	windowData.window[mWindowID] = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);

	glfwSetWindowSizeCallback(windowData.window[mWindowID], windowSizeCallback);

	mCreated = true;
}

void Window::Create(int width, int height, const char* title)
{
	if (mCreated == false)
	{
		mWindowID = windowData.id;
		windowData.id++;

		mWidth = width;
		mHeight = height;
		mTitle = title;
		mVSync = false;

		windowData.window[mWindowID] = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);

		glfwSetWindowSizeCallback(windowData.window[mWindowID], windowSizeCallback);

		mCreated = true;
	}
}

void Window::SetTitle(const char* title)
{
	glfwSetWindowTitle(windowData.window[mWindowID], title);
}

void Window::SetSize(int width, int height)
{
	glfwSetWindowSize(windowData.window[mWindowID], width, height);
}

void Window::SetVSync(bool vSync)
{
	glfwSwapInterval(vSync);
}

void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(windowData.window[mWindowID]);
}

bool Window::GetWindowShouldClose()
{
	if (glfwWindowShouldClose(windowData.window[mWindowID]))
		return true;
	else
		return false;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(windowData.window[mWindowID]);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}