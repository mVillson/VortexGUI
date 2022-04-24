#include "Texture.h"

#include "GLEW/glew.h"
#include "..\..\vendor\stb_image\stb_image.h"

unsigned int Texture::LoadTexture(const std::string& filepath)
{
	int width, height, bits;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* pixels = stbi_load(filepath.c_str(), &width, &height, &bits, STBI_rgb_alpha);

	unsigned int textureID;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	stbi_image_free(pixels);

	return textureID;
}

void Texture::Bind(unsigned int textureID, unsigned int slot /* = 0 */)
{
	glBindTextureUnit(slot, textureID);
}