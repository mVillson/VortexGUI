#include "Renderer2D.h"

#include "GLEW\glew.h"

#include "..\..\vendor\stb_image\stb_image.h"

#include "ShaderProgram.h"

static const unsigned int MaxQuadCount = 1000;
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

	unsigned int TextureSlots[MaxTextureSlots];
	unsigned int TextureSlotIndex = 0;

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
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, Color)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, TexCoord)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, TexIndex)));
	glEnableVertexAttribArray(3);

	sData.sp.Create();

	std::string texture;
	std::stringstream texSlot;
	for (int i = 0; i < 31; i++)
	{
		texture = "uTexture";
		texSlot.str("");
		texSlot << i;
		texture += texSlot.str().c_str();
		sData.sp.SetUniform1i(texture.c_str(), i);
	}

	for (unsigned int i = 0; i < MaxTextureSlots; i++)
		sData.TextureSlots[i] = 0;
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
	for (unsigned int i = 0; i < sData.TextureSlotIndex; i++)
	{
		glBindTextureUnit(i, sData.TextureSlots[i]);
	}

	glBindVertexArray(sData.va);
	glDrawElements(GL_TRIANGLES, 6 * sData.CurrentQuads, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::ShutDown()
{
	glDeleteVertexArrays(1, &sData.va);
	glDeleteBuffers(1, &sData.vb);
	glDeleteBuffers(1, &sData.ib);

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

	float index = -1.0f;

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

void Renderer2D::DrawTexture(const vec2& position, const vec2& size, int textureID, const vec4& tintColor)
{
	if (sData.CurrentQuads >= MaxQuadCount || sData.TextureSlotIndex > 32)
	{
		EndBatch();
		Flush();
		BeginBatch();

		sData.CurrentQuads = 0;
	}

	
	float textureIndex = 0.0f;
	for (unsigned int i = 1; i < sData.TextureSlotIndex; i++)
	{
		if (sData.TextureSlots[i] == textureID)
		{
			textureIndex = (float)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		textureIndex = (float)sData.TextureSlotIndex;
		sData.TextureSlots[sData.TextureSlotIndex] = textureID;
		sData.TextureSlotIndex+=1;
	}
	

	sData.QuadBufferPtr->Position = { position.x, position.y, 0.0f };
	sData.QuadBufferPtr->Color = tintColor;
	sData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
	sData.QuadBufferPtr->TexIndex = textureIndex;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
	sData.QuadBufferPtr->Color = tintColor;
	sData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
	sData.QuadBufferPtr->TexIndex = textureIndex;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
	sData.QuadBufferPtr->Color = tintColor;
	sData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
	sData.QuadBufferPtr->TexIndex = textureIndex;
	sData.QuadBufferPtr++;

	sData.QuadBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
	sData.QuadBufferPtr->Color = tintColor;
	sData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
	sData.QuadBufferPtr->TexIndex = textureIndex;
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