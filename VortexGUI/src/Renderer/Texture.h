#pragma once

#include "..\Core.h"

class VORTEX_API Texture
{
public:
	static unsigned int LoadTexture(const std::string& filepath);
	static void Bind(unsigned int textureID, unsigned int slot = 0);
};