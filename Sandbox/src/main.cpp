#include "..\..\VortexGUI\VortexGUI.h"

int main()
{
	Window window(800, 600, "C++ & OpenGL");
	window.MakeContextCurrent();

	Gui gui(window);
	Event event(window);

	Renderer2D::Init();

	Renderer2D::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	auto texture1 = Texture::LoadTexture("assets/wooden_crate.jpg");
	auto texture2 = Texture::LoadTexture("assets/metal.jfif");

	while (!window.GetWindowShouldClose())
	{
		Event::PollEvents();
		
		Renderer2D::Clear();

		Renderer2D::BeginBatch();
		
		Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.25f, 0.25f }, { 0.97f, 0.93f, 0.13f, 1.0f });

		Renderer2D::DrawTexture({ -0.20f, -0.5f }, { 0.25f, 0.25f }, texture1, { 0.7f, 1.0f, 0.8f, 1.0f });

		Renderer2D::DrawTexture({ 0.10f, -0.5f }, { 0.25f, 0.25f }, texture2, { 1.0f, 0.5f, 1.0f, 1.0f });

		Renderer2D::EndBatch();

		Renderer2D::Flush();

		if (event.IfMouseButtonPressed(MouseButton::LEFT))
			Renderer2D::Wireframe(true);
		else if (event.IfMouseButtonReleased(MouseButton::RIGHT))
			Renderer2D::Wireframe(false);

		window.SwapBuffers();
	}

	Renderer2D::ShutDown();
	Gui::Shutdown();
	return 0;
}