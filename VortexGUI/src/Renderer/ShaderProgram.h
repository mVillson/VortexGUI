#pragma once

#include "..\Core.h"
#include "..\..\vendor\glm\glm.hpp"
#include "..\..\Vendor\glm\gtc\type_ptr.hpp"

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
	void SetUniform2f(const std::string& name, const glm::vec2& v);
	void SetUniform3f(const std::string& name, const glm::vec3& v);
	void SetUniform4f(const std::string& name, const glm::vec4& v);
	void SetUniformMatrix(const std::string& name, const glm::mat4& m);

	unsigned int GetProgram() { return mProgram; }
};