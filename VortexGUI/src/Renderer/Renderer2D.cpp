#include "Renderer2D.h"

#include "GLEW/glew.h"

#include "..\..\vendor\stb_image\stb_image.h"

#include "ShaderProgram.h"

static const unsigned int MaxQuadCount = 100;
static const unsigned int MaxVertexCount = 4 * MaxQuadCount;
static const unsigned int MaxIndexCount = 6 * MaxQuadCount;
static const unsigned int MaxTextureSlots = 32;

struct Vertex
{
	vec3 Position;
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
};

struct RendererData
{
	unsigned int va = 0;
	unsigned int vb = 0;
	unsigned int ib = 0;

	Vertex* QuadBuffer = nullptr;
	Vertex* QuadBufferPtr = nullptr;

	unsigned int CurrentQuads = 0;

	unsigned int WhiteTexture;

	ShaderProgram sp;
};

static RendererData sData;

void Renderer2D::Init()
{
	sData.QuadBuffer = new Vertex[MaxVertexCount];

	glCreateVertexArrays(1, &sData.va);
	glBindVertexArray(sData.va);

	glCreateBuffers(1, &sData.vb);
	glBindBuffer(GL_ARRAY_BUFFER, sData.vb);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	unsigned int offset = 0;
	std::array<unsigned int, MaxIndexCount> indices;

	for (unsigned int i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i+0] = 0 + offset;
		indices[i+1] = 1 + offset;
		indices[i+2] = 2 + offset;
	
		indices[i+3] = 2 + offset;
		indices[i+4] = 3 + offset;
		indices[i+5] = 0 + offset;
	
		offset += 4;
	}
	
	glCreateBuffers(1, &sData.ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sData.ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, Position)));
	glEnableVertexArrayAttrib(sData.va, 0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, Color)));
	glEnableVertexArrayAttrib(sData.va, 1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, TexCoord)));
	glEnableVertexArrayAttrib(sData.va, 2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, TexIndex)));
	glEnableVertexArrayAttrib(sData.va, 3);

	// 1x1 white texture
	glCreateTextures(GL_TEXTURE_2D, 1, &sData.WhiteTexture);
	glBindTexture(GL_TEXTURE_2D, sData.WhiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	unsigned int color = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

	glBindTextureUnit(0, sData.WhiteTexture);

	int samplers[32];
	for (int i = 0; i < 32; i++)
	{
		samplers[i] = i;
	}

	glUniform1iv(glGetUniformLocation(sData.sp.GetProgram(), "uTextures"), 32, samplers);

	sData.sp.Create();
}

void Renderer2D::BeginBatch()
{
	sData.QuadBufferPtr = sData.QuadBuffer;
}

void Renderer2D::EndBatch()
{
	glBindBuffer(GL_ARRAY_BUFFER, sData.vb);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sData.CurrentQuads * 4 * sizeof(Vertex), sData.QuadBuffer);
}

void Renderer2D::Flush()
{
	glBindVertexArray(sData.va);
	glDrawElements(GL_TRIANGLES, 6 * sData.CurrentQuads, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::ShutDown()
{
	glDeleteVertexArrays(1, &sData.va);
	glDeleteBuffers(1, &sData.vb);
	glDeleteBuffers(1, &sData.ib);

	glDeleteTextures(1, &sData.WhiteTexture);

	delete[] sData.QuadBuffer;
}

void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const vec4& color)
{
	if (sData.CurrentQuads >= MaxQuadCount)
	{
		EndBatch();
		Flush();
		BeginBatch();

		sData.CurrentQuads = 0;
	}

	float index = 0.0f;

	sData.QuadBufferPtr->Position = { position.x, position.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
	sData.QuadBufferPtr->TexIndex = index;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
	sData.QuadBufferPtr->TexIndex = index;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
	sData.QuadBufferPtr->TexIndex = index;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
	sData.QuadBufferPtr->TexIndex = index;
	sData.QuadBufferPtr++;

	sData.CurrentQuads++;
}

void Renderer2D::DrawQuad(const vec2& position, const vec2& size, unsigned int textureID)
{
	if (sData.CurrentQuads >= MaxQuadCount)
	{
		EndBatch();
		Flush();
		BeginBatch();

		sData.CurrentQuads = 0;
	}

	const vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	sData.QuadBufferPtr->Position = { position.x, position.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
	sData.QuadBufferPtr->TexIndex = textureID;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
	sData.QuadBufferPtr->TexIndex = textureID;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
	sData.QuadBufferPtr->TexIndex = textureID;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
	sData.QuadBufferPtr->Color = color;
	sData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
	sData.QuadBufferPtr->TexIndex = textureID;
	sData.QuadBufferPtr++;

	sData.CurrentQuads++;
}

void Renderer2D::ClearColor(const vec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void Renderer2D::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

// Extra
void InitOpenGL()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		printf("Error: OpenGL could not initialize correctly!");
}

unsigned int LoadTexture(const std::string& filepath)
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

void BindTextureSlot(unsigned int slot, unsigned int textureID)
{
	glBindTextureUnit(slot, textureID);
};