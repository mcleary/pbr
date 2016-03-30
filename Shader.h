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
	Shader(ShaderType type, const std::string& sourceFile);

    GLuint shaderID();

private:
	bool _compileShader();

	ShaderType m_ShaderType;
	std::string m_ShaderSourceFile;
	std::string m_ShaderSource;
	GLuint m_ShaderID;
};

class Program
{
public:
    Program();

    void attach(Shader* shader);
    void link();

    void bind();
    void unbind();

private:
	GLuint m_ProgramID;
};
