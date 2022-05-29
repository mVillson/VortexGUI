#pragma once

#include "..\Core.h"
#include "..\..\vendor\glm\glm.hpp"

class VORTEX_API Renderer2D
{
public:
	static void Init();
	static void ShutDown();

	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	static void ClearColor(const glm::vec4& color);
	static void Clear();

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawTexture(const glm::vec2& position, const glm::vec2& size, int textureID, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

	static void Wireframe(bool wireframe = true);
};
