#include "Shader.h"

#include <iostream>

void compile_info(const GLuint shader)
{
	GLint status(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (1 != status)
	{
		GLint maxLength(0);
		GLint logLength(0);

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar * log = new GLchar[maxLength];
		glGetShaderInfoLog(shader, maxLength, &logLength, log);

		std::cout << "Compiling shader failed." << std::endl
			<< log << std::endl;
	}
}

void link_info(const GLuint program)
{
	GLint status(0);
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (1 != status)
	{
		GLint maxLength(0);
		GLint logLength(0);

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar * log = new GLchar[maxLength];
		glGetProgramInfoLog(program, maxLength, &logLength, log);

		std::cout << "Linking program failed." << std::endl
			<< log << std::endl;
	}
}

Shader::Shader(ShaderType type, const std::string & source) :
	m_ShaderType(type),
	m_ShaderSource(source)
{
	//m_ShaderID = glCreateShader(static_cast<GLenum>(m_ShaderType));
	m_ShaderID = glCreateShader(GL_VERTEX_SHADER);

	const char* shaderSource = m_ShaderSource.data();
	glShaderSource(m_ShaderID, 1, &shaderSource, nullptr);
	glCompileShader(m_ShaderID);
	compile_info(m_ShaderID);
}
