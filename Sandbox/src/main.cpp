#include "..\..\VortexGUI\VortexGUI.h"

#include "GLFW/glfw3.h"

int main()
{
	if (!glfwInit())
		printf("Error: GLFW could not initialize correctly!");

	GLFWwindow* window = glfwCreateWindow(800, 600, "C++ & OpenGL", NULL, NULL);

	glfwMakeContextCurrent(window);

	InitOpenGL();

	Renderer2D::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	
	auto texture1 = LoadTexture("assets/wooden_crate.jpg");
	BindTextureSlot(1, texture1);

	Renderer2D::Init();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		Renderer2D::Clear();

		Renderer2D::BeginBatch();
		
		Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.25f, 0.25f }, { 0.97f, 0.93f, 0.13f, 1.0f });

		Renderer2D::DrawQuad({ -0.20f, -0.5f }, { 0.25f, 0.25f }, texture1);

		Renderer2D::EndBatch();

		Renderer2D::Flush();

		glfwSwapBuffers(window);
	}
	
	Renderer2D::ShutDown();

	return 0;
}