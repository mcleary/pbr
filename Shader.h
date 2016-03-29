#pragma once

#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>
using namespace gl;

enum class ShaderType
{
	ShaderType_VERTEX   = static_cast<GLuint>(GL_VERTEX_SHADER), 
	ShaderType_TESSCRTL = static_cast<GLuint>(GL_TESS_CONTROL_SHADER),
	ShaderType_TESSEVAL = static_cast<GLuint>(GL_TESS_EVALUATION_SHADER),
	ShaderType_GEOMETRY = static_cast<GLuint>(GL_GEOMETRY_SHADER),
	ShaderType_FRAGMENT = static_cast<GLuint>(GL_FRAGMENT_SHADER),
};

class Shader
{
public:
	Shader(ShaderType type, const std::string& source);		

private:
	bool _compileShader();

	ShaderType m_ShaderType;
	const std::string m_ShaderSource;
	GLuint m_ShaderID;
};

class Program
{
private:
	GLuint m_ProgramID;
};