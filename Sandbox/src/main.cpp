#include "..\..\VortexGUI\VortexGUI.h"

int main()
{
	Window window(800, 600, "GUI Framework by Villson");
	Event event(window);
	Gui gui(window, event);

	auto texture1 = Texture::LoadTexture("assets/wooden_crate.jpg");
	auto texture2 = Texture::LoadTexture("assets/metal.jfif");

	while (!window.GetWindowShouldClose())
	{
		Event::PollEvents();
		window.SetViewport(0, window.GetWidth(), 0, window.GetHeight());
		window.RetrieveEvents();

		Renderer2D::Clear();

		gui.Begin();

		// Button
		static bool pressed = false;
		gui.Button(pressed, 12.0f, window.GetHeight() - 30.0f, 35.0f, 20.0f);
		if (pressed)
			Renderer2D::DrawQuad({ 100.0f, 100.0f }, { 100.0f, 100.0f }, { 1.0f, 0.0f, 1.0f, 1.0f});

		// Slider
		float value;
		gui.Slider(value, 100.0f, 600.0f, 12.0f, window.GetHeight() - 90.0f, 100.0f, 20.0f);

		// Checkbox 1
		static bool toggle = false;
		gui.CheckBox(toggle, 12.0f, window.GetHeight() - 60.0f, 20.0f);
		if (toggle)
			Renderer2D::DrawQuad({ value, 350.0f }, { 100.0f, 100.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });

		// Checkbox 2
		static bool toggle2;
		gui.CheckBox(toggle2, 12.0f, window.GetHeight() - 120.0f, 20.0f);
		Renderer2D::Wireframe(toggle2);

		Renderer2D::DrawTexture({ 300.0f, 100.0f }, { 100.0f, 100.0f }, texture1, { 0.7f, 1.0f, 0.8f, 1.0f });

		Renderer2D::DrawTexture({ 500.0f, 100.0f }, { 100.0f, 100.0f }, texture2, { 0.9f, 0.5f, 0.9f, 1.0f });
		
		gui.End();

		gui.Draw();

		window.SwapBuffers();
	}

	Gui::Shutdown();
	return 0;
}