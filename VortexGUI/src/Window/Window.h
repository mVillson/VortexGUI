#pragma once

#include "..\Core.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

class VORTEX_API Window
{
private:
	GLFWwindow* mWindow;
	int mWidth, mHeight;
	const char* mTitle;
	bool mVSync;
	bool mCreated;
public:
	Window();
	Window(int width, int height, const char* title);
	void Construct(int width, int height, const char* title);

	void MakeContextCurrent();
	void SwapBuffers();

	// setters
	void SetTitle(const char* title);
	void SetSize(int width, int height);
	void SetVSync(bool vSync = true);

	//getters
	GLFWwindow* GetWindow() const;
	int GetWidth() const;
	int GetHeight() const;
	bool GetWindowShouldClose() const;
	bool GetCreated() const;
};