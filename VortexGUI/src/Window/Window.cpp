#include "Window.h"

// Window Class

bool init = false;

void windowSizeCallback(GLFWwindow* window, int width, int height);

Window::Window()
	:mWidth(0), mHeight(0), mCursorPosX(0.0), mCursorPosY(0.0), mTitle(""), mVSync(false), mCreated(false)
{
	if (init == false)
	{
		if (!glfwInit())
		{
			printf("Error: Glfw Could Not Initialize!");
		}
		init = true;
	}

	mWindow = nullptr;
}

Window::Window(int width, int height, const char* title)
	:mCursorPosX(0.0), mCursorPosY(0.0)
{
	if (init == false)
	{
		if (!glfwInit())
		{
			printf("Error: Glfw Could Not Initialize!");
		}
		init = true;
	}

	mWidth = width;
	mHeight = height;
	mTitle = title;
	mVSync = false;

	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);

	glfwSetWindowSizeCallback(mWindow, windowSizeCallback);

	mCreated = true;
}

void Window::Construct(int width, int height, const char* title)
{
	if (mCreated == false)
	{
		if (init == false)
		{
			if (!glfwInit())
			{
				printf("Error: Glfw Could Not Initialize!");
			}
			init = true;
		}

		mWidth = width;
		mHeight = height;
		mTitle = title;
		mVSync = false;

		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);

		glfwSetWindowSizeCallback(mWindow, windowSizeCallback);

		mCreated = true;
	}
	else
	{
		printf("Error: Window already created!");
	}
}

void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(mWindow);
}

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//setters
void Window::SetTitle(const char* title)
{
	glfwSetWindowTitle(mWindow, title);
}

void Window::SetSize(int width, int height)
{
	glfwSetWindowSize(mWindow, width, height);
}

void Window::SetVSync(bool vSync)
{
	glfwSwapInterval(vSync);
}

// getters
GLFWwindow* Window::GetWindow() const
{
	return mWindow;
}

int Window::GetWidth()
{
	glfwGetWindowSize(mWindow, &mWidth, &mHeight);
	return mWidth;
}

int Window::GetHeight()
{
	glfwGetWindowSize(mWindow, &mWidth, &mHeight);
	return mHeight;
}

double Window::GetCursorPosX()
{
	glfwGetCursorPos(mWindow, &mCursorPosX, &mCursorPosY);
	return mCursorPosX;
}

double Window::GetCursorPosY()
{
	glfwGetCursorPos(mWindow, &mCursorPosX, &mCursorPosY);
	return (double)mHeight - mCursorPosY;
}

bool Window::GetWindowShouldClose() const
{
	if (glfwWindowShouldClose(mWindow))
		return true;
	else
		return false;
}

bool Window::GetCreated() const
{
	return mCreated;
}