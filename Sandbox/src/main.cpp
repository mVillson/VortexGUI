#include "..\..\VortexGUI\VortexGUI.h"

#include <iostream>

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
		// shit beigns
		window.SetVSync(false);
		static bool a = false;
		if (window.GetCursorPosX() >= 100.0f && window.GetCursorPosX() <= 200.0f)
		{
			if (window.GetCursorPosY() >= 100.0f && window.GetCursorPosY() <= 200.0f)
			{
				Renderer2D::DrawQuad({ 100.0f, 100.0f }, { 100.0f, 100.0f }, { 0.91f, 0.86f, 0.17f, 1.0f });
				a = true;
				if (event.IfMouseButtonPressed(MouseButton::LEFT))
					Renderer2D::Wireframe(true);
			}
		}

		if (a == false)
			Renderer2D::DrawQuad({ 100.0f, 100.0f }, { 100.0f, 100.0f }, { 0.97f, 0.94f, 0.16f, 1.0f });

		a = false;

		if (event.IfMouseButtonReleased(MouseButton::LEFT))
			Renderer2D::Wireframe(false);
		// shit ends

		Renderer2D::DrawTexture({ 300.0f, 100.0f }, { 100.0f, 100.0f }, texture1, { 0.7f, 1.0f, 0.8f, 1.0f });

		Renderer2D::DrawTexture({ 500.0f, 100.0f }, { 100.0f, 100.0f }, texture2, { 1.0f, 0.5f, 1.0f, 1.0f });
	
		Renderer2D::EndBatch();

		Renderer2D::SetModel(glm::mat4(1.0f));
		Renderer2D::SetView(glm::ortho(0.0f, (float)window.GetWidth(), 0.0f, (float)window.GetHeight()));
		Renderer2D::SetProjection(glm::mat4(1.0f));

		Renderer2D::Flush();

		window.SwapBuffers();
	}

	Renderer2D::ShutDown();
	Gui::Shutdown();
	return 0;
}