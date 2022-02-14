#pragma once

#include "..\Core.h"
#include "..\Math\SimpleMath.h"

class VORTEX_API ShaderProgram
{
private:
	unsigned int mProgram;
public:
	ShaderProgram();

	void Create();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int i);
	void SetUniform1iv(const std::string& name, unsigned int count, const int* value);

	void SetUniform2f(const std::string& name, const vec2& v);
	void SetUniform3f(const std::string& name, const vec3& v);
	void SetUniform4f(const std::string& name, const vec4& v);

	unsigned int GetProgram() { return mProgram; }
};