#pragma once

#include "..\Core.h"

bool VORTEX_API InitGlfw();
void VORTEX_API ShutdownGlfw();

class VORTEX_API Window
{
private:
	int mWindowID;
	int mWidth, mHeight;
	const char* mTitle;
	bool mVSync;
	bool mCreated;
public:
	Window();
	Window(int width, int height, const char* title);
	void Create(int width, int height, const char* title);
	void SetTitle(const char* title);
	void SetSize(int width, int height);
	void SetVSync(bool vSync = true);
	void MakeContextCurrent();
	bool GetWindowShouldClose();
	void SwapBuffers();
	void PollEvents();
};