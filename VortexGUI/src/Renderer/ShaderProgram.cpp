#include "ShaderProgram.h"

#include "GLEW/glew.h"

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

		uniform mat4 uMvp;
		
		void main()
		{
			vPos = pos;
			vColor = color;
			vTexCoord = texCoord;
			vTexIndex = texIndex;
			gl_Position = uMvp * vec4(pos, 1.0);
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
		
		uniform sampler2D uTexture[32];
		
		void main()
		{
			int index = int(vTexIndex);
			
			if (index == -1)
			{
				color = vColor;
			}
			else
			{
				color = texture(uTexture[index], vTexCoord) * vColor;
			}
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

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (mUniformLocations.find(name) != mUniformLocations.end())
		return mUniformLocations[name];

	auto loc = glGetUniformLocation(mProgram, name.c_str());
	mUniformLocations[name] = loc;
	return loc;
}

void ShaderProgram::SetUniform1i(const std::string& name, int i)
{
	auto loc = GetUniformLocation(name);
	glUniform1i(loc, i);
}

void ShaderProgram::SetUniform1iv(const std::string& name, unsigned int count, const int* value)
{
	auto loc = GetUniformLocation(name);
	glUniform1iv(loc, count, value);
}

void ShaderProgram::SetUniform2f(const std::string& name, const glm::vec2& v)
{
	auto loc = GetUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::SetUniform3f(const std::string& name, const glm::vec3& v)
{
	auto loc = GetUniformLocation(name);
	glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::SetUniform4f(const std::string& name, const glm::vec4& v)
{
	auto loc = GetUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::SetUniformMatrix(const std::string& name, const glm::mat4& m)
{
	auto loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(m));
}