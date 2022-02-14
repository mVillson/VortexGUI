#include "ShaderProgram.h"

#include <GLEW/glew.h>

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
		
		out vec4 vColor;
		out vec2 vTexCoord;
		out float vTexIndex;
		
		void main()
		{
			vColor = color;
			vTexCoord = texCoord;
			vTexIndex = texIndex;
			gl_Position = vec4(pos, 1.0);
		}
		)V0G0N";

	const char* fsSrc =
		R"V0G0N(
		#version 450 core
		
		in vec4 vColor;
		in vec2 vTexCoord;
		in float vTexIndex;
		
		out vec4 color;
		
		uniform sampler2D uTextures[32];
		
		void main()
		{
			int index = int(vTexIndex);
			color = texture(uTextures[index], vTexCoord) * vColor;
		};
		)V0G0N";

	glShaderSource(vs, 1, &vsSrc, nullptr);
	glShaderSource(fs, 1, &fsSrc, nullptr);

	glCompileShader(vs);
	glCompileShader(fs);

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