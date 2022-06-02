#pragma once

#include "..\Core.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

class VORTEX_API Window
{
private:
	GLFWwindow* mWindow;
	int mWidth, mHeight;
	double mCursorPosX, mCursorPosY;
	const char* mTitle;
	bool mVSync;
	bool mCreated;
public:
	Window();
	Window(int width, int height, const char* title);
	void Construct(int width, int height, const char* title);

	void MakeContextCurrent();
	void SwapBuffers();
	void RetrieveEvents();

	// setters
	void SetTitle(const char* title);
	void SetSize(int width, int height);
	void SetViewport(int left, int right, int bottom, int top);
	void SetVSync(bool vSync = true);

	//getters
	GLFWwindow* GetWindow() const;
	int GetWidth();
	int GetHeight();
	double GetCursorPosX();
	double GetCursorPosY();
	bool GetWindowShouldClose() const;
	bool GetCreated() const;
};