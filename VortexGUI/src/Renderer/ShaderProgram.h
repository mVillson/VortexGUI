#pragma once

#include "..\Core.h"
#include "..\..\vendor\glm\glm.hpp"
#include "..\..\Vendor\glm\gtc\type_ptr.hpp"

class ShaderProgram
{
private:
	unsigned int mProgram;
	std::unordered_map<std::string, int> mUniformLocations;
public:
	VORTEX_API ShaderProgram();

	VORTEX_API void Create();

	VORTEX_API void Bind() const;
	VORTEX_API void Unbind() const;

	VORTEX_API unsigned int GetProgram() { return mProgram; }
	VORTEX_API int GetUniformLocation(const std::string& name);

	VORTEX_API void SetUniform1i(const std::string& name, int i);
	VORTEX_API void SetUniform1iv(const std::string& name, unsigned int count, const int* value);
	VORTEX_API void SetUniform2f(const std::string& name, const glm::vec2& v);
	VORTEX_API void SetUniform3f(const std::string& name, const glm::vec3& v);
	VORTEX_API void SetUniform4f(const std::string& name, const glm::vec4& v);
	VORTEX_API void SetUniformMatrix(const std::string& name, const glm::mat4& m);
};