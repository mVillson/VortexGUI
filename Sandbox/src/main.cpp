#include "..\..\VortexGUI\VortexGUI.h"

int main()
{
	Window::InitGlfw();
	Window::CreateWindow(800, 600, "C++ & OpenGL");

	InitOpenGL();

	Renderer2D::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	
	auto texture1 = Texture::LoadTexture("assets/wooden_crate.jpg");
	auto texture2 = Texture::LoadTexture("assets/metal.jfif");

	Renderer2D::Init();

	while (!Window::GetWindowShouldClose())
	{
		Window::PollEvents();
		
		Renderer2D::Clear();

		Renderer2D::BeginBatch();
		
		Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.25f, 0.25f }, { 0.97f, 0.93f, 0.13f, 1.0f });

		Renderer2D::DrawTexture({ -0.20f, -0.5f }, { 0.25f, 0.25f }, texture1, { 0.7f, 1.0f, 0.8f, 1.0f });

		Renderer2D::DrawTexture({ 0.10f, -0.5f }, { 0.25f, 0.25f }, texture2, { 1.0f, 1.0f, 1.0f, 1.0f });

		Renderer2D::EndBatch();

		Renderer2D::Flush();

		Window::SwapBuffers();
	}
	
	Renderer2D::ShutDown();
	Window::Shutdown();

	return 0;
}