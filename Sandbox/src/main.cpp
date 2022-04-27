#include "..\..\VortexGUI\VortexGUI.h"

int main()
{
	InitGlfw();
	Window window(800, 600, "C++ & OpenGL");

	window.MakeContextCurrent();
	
	InitOpenGL();

	Renderer2D::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Renderer2D::Wireframe(true);
	
	auto texture1 = Texture::LoadTexture("assets/wooden_crate.jpg");
	auto texture2 = Texture::LoadTexture("assets/metal.jfif");

	Renderer2D::Init();

	while (!window.GetWindowShouldClose())
	{
		window.PollEvents();
		
		Renderer2D::Clear();

		Renderer2D::BeginBatch();
		
		Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.25f, 0.25f }, { 0.97f, 0.93f, 0.13f, 1.0f });

		Renderer2D::DrawTexture({ -0.20f, -0.5f }, { 0.25f, 0.25f }, texture1, { 0.7f, 1.0f, 0.8f, 1.0f });

		Renderer2D::DrawTexture({ 0.10f, -0.5f }, { 0.25f, 0.25f }, texture2, { 1.0f, 0.5f, 1.0f, 1.0f });

		Renderer2D::EndBatch();

		Renderer2D::Flush();

		window.SwapBuffers();
	}
	
	Renderer2D::ShutDown();
	ShutdownGlfw();

	return 0;
}