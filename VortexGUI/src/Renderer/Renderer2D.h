#pragma once

#include "..\Core.h"
#include "..\Math\SimpleMath.h"

VORTEX_API void InitOpenGL();

VORTEX_API unsigned int LoadTexture(const std::string& filepath);

VORTEX_API void BindTextureSlot(unsigned int slot, unsigned int textureID);

class VORTEX_API Renderer2D
{
public:
	static void Init();
	static void ShutDown();

	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	static void ClearColor(const vec4& color);
	static void Clear();

	static void DrawQuad(const vec2& position, const vec2& size, const vec4& color);
	static void DrawQuad(const vec2& position, const vec2& size, int textureID, const vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
};
