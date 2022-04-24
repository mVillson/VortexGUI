#include "ShaderProgram.h"

#include "GLEW\glew.h"

#include <iostream>

ShaderProgram::ShaderProgram()
	:mProgram(0)
{

}

void ShaderProgram::Create()
{
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char* vsSrc = 
		R"V0G0N(
		#version 450 core
		
		layout(location = 0) in vec3 pos;
		layout(location = 1) in vec4 color;
		layout(location = 2) in vec2 texCoord;
		layout(location = 3) in float texIndex;
		
		out vec3 vPos;
		out vec4 vColor;
		out vec2 vTexCoord;
		out float vTexIndex;
		
		void main()
		{
			vPos = pos;
			vColor = color;
			vTexCoord = texCoord;
			vTexIndex = texIndex;
			gl_Position = vec4(pos, 1.0);
		}
		)V0G0N";

	const char* fsSrc =
		R"V0G0N(
		#version 450 core
		
		in vec3 vPos;
		in vec4 vColor;
		in vec2 vTexCoord;
		in float vTexIndex;
		
		out vec4 color;
		
		uniform sampler2D uTexture0;
		uniform sampler2D uTexture1;
		uniform sampler2D uTexture2;
		uniform sampler2D uTexture3;
		uniform sampler2D uTexture4;
		uniform sampler2D uTexture5;
		uniform sampler2D uTexture6;
		uniform sampler2D uTexture7;
		uniform sampler2D uTexture8;
		uniform sampler2D uTexture9;
		uniform sampler2D uTexture10;
		uniform sampler2D uTexture11;
		uniform sampler2D uTexture12;
		uniform sampler2D uTexture13;
		uniform sampler2D uTexture14;
		uniform sampler2D uTexture15;
		uniform sampler2D uTexture16;
		uniform sampler2D uTexture17;
		uniform sampler2D uTexture18;
		uniform sampler2D uTexture19;
		uniform sampler2D uTexture20;
		uniform sampler2D uTexture21;
		uniform sampler2D uTexture22;
		uniform sampler2D uTexture23;
		uniform sampler2D uTexture24;
		uniform sampler2D uTexture25;
		uniform sampler2D uTexture26;
		uniform sampler2D uTexture27;
		uniform sampler2D uTexture28;
		uniform sampler2D uTexture29;
		uniform sampler2D uTexture30;
		uniform sampler2D uTexture31;
		
		void main()
		{
			int index = int(vTexIndex);

			switch (index)
			{
				case -1:
					color = vColor;
					break;
				case 0:
					color = texture(uTexture0, vTexCoord) * vColor;
					break;
				case 1:
					color = texture(uTexture1, vTexCoord) * vColor;
					break;
				case 2:
					color = texture(uTexture2, vTexCoord) * vColor;
					break;
				case 3:
					color = texture(uTexture3, vTexCoord) * vColor;
					break;
				case 4:
					color = texture(uTexture4, vTexCoord) * vColor;
					break;
				case 5:
					color = texture(uTexture5, vTexCoord) * vColor;
					break;
				case 6:
					color = texture(uTexture6, vTexCoord) * vColor;
					break;
				case 7:
					color = texture(uTexture7, vTexCoord) * vColor;
					break;
				case 8:
					color = texture(uTexture8, vTexCoord) * vColor;
					break;
				case 9:
					color = texture(uTexture9, vTexCoord) * vColor;
					break;
				case 10:
					color = texture(uTexture10, vTexCoord) * vColor;
					break;
				case 11:
					color = texture(uTexture11, vTexCoord) * vColor;
					break;
				case 12:
					color = texture(uTexture12, vTexCoord) * vColor;
					break;
				case 13:
					color = texture(uTexture13, vTexCoord) * vColor;
					break;
				case 14:
					color = texture(uTexture14, vTexCoord) * vColor;
					break;
				case 15:
					color = texture(uTexture15, vTexCoord) * vColor;
					break;
				case 16:
					color = texture(uTexture16, vTexCoord) * vColor;
					break;
				case 17:
					color = texture(uTexture17, vTexCoord) * vColor;
					break;
				case 18:
					color = texture(uTexture18, vTexCoord) * vColor;
					break;
				case 19:
					color = texture(uTexture19, vTexCoord) * vColor;
					break;
				case 20:
					color = texture(uTexture20, vTexCoord) * vColor;
					break;
				case 21:
					color = texture(uTexture21, vTexCoord) * vColor;
					break;
				case 22:
					color = texture(uTexture22, vTexCoord) * vColor;
					break;
				case 23:
					color = texture(uTexture23, vTexCoord) * vColor;
					break;
				case 24:
					color = texture(uTexture24, vTexCoord) * vColor;
					break;
				case 25:
					color = texture(uTexture25, vTexCoord) * vColor;
					break;
				case 26:
					color = texture(uTexture26, vTexCoord) * vColor;
					break;
				case 27:
					color = texture(uTexture27, vTexCoord) * vColor;
					break;
				case 28:
					color = texture(uTexture28, vTexCoord) * vColor;
					break;
				case 29:
					color = texture(uTexture29, vTexCoord) * vColor;
					break;
				case 30:
					color = texture(uTexture30, vTexCoord) * vColor;
					break;
				case 31:
					color = texture(uTexture31, vTexCoord) * vColor;
					break;
				default:
					color = vColor;
					break;
			};
		};
		)V0G0N";

	glShaderSource(vs, 1, &vsSrc, nullptr);
	glShaderSource(fs, 1, &fsSrc, nullptr);

	int isCompiled = 0;
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == 0)
	{
		printf("Error: Vertex shader did not compile!");
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == 0)
	{
		printf("Error: Fragment shader did not compile!");
	}

	mProgram = glCreateProgram();

	glAttachShader(mProgram, vs);
	glAttachShader(mProgram, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	glLinkProgram(mProgram);
	glValidateProgram(mProgram);
	glUseProgram(mProgram);
}

void ShaderProgram::Bind() const
{
	glUseProgram(mProgram);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::SetUniform1i(const std::string& name, int i)
{
	auto loc = glGetUniformLocation(mProgram, name.c_str());
	glUniform1i(loc, i);
}

void ShaderProgram::SetUniform1iv(const std::string& name, unsigned int count, const int* value)
{
	auto loc = glGetUniformLocation(mProgram, name.c_str());
	glUniform1iv(loc, count, value);
}

void ShaderProgram::SetUniform2f(const std::string& name, const vec2& v)
{
	auto loc = glGetUniformLocation(mProgram, name.c_str());
	glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::SetUniform3f(const std::string& name, const vec3& v)
{
	auto loc = glGetUniformLocation(mProgram, name.c_str());
	glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::SetUniform4f(const std::string& name, const vec4& v)
{
	auto loc = glGetUniformLocation(mProgram, name.c_str());
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}