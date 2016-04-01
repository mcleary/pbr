#include "Shader.h"

#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

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
        
        throw std::runtime_error(std::string("Compiling shader failed.\n") + std::string(log));
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
        
        throw std::runtime_error(std::string("Linking program failed.\n") + std::string(log));
	}
}

Shader::Shader(ShaderType type, const std::string & sourceFile) :
	m_ShaderType(type),
	m_ShaderSourceFile(sourceFile)
{
	std::ifstream file(m_ShaderSourceFile);
	if (file.is_open())
	{
		m_ShaderSource.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());		
	}	

	m_ShaderID = glCreateShader(static_cast<GLenum>(m_ShaderType));

	const char* shaderSource = m_ShaderSource.data();
	glShaderSource(m_ShaderID, 1, &shaderSource, nullptr);
	glCompileShader(m_ShaderID);
    
    try
    {
        compile_info(m_ShaderID);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error compiling shader '" << sourceFile << "'" << std::endl;
        std::cerr << "Details: " << e.what() << std::endl;
    }
	
}

GLuint Shader::shaderID()
{
    return m_ShaderID;
}

Program::Program()
{
    m_ProgramID = glCreateProgram();
}

void Program::attach(Shader* shader)
{
    glAttachShader(m_ProgramID, shader->shaderID());
}

void Program::link()
{
    glLinkProgram(m_ProgramID);
    
    try
    {
        link_info(m_ProgramID);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error linking program." << std::endl;
        std::cerr << "Details: " << e.what() << std::endl;
    }
    
}

void Program::setUniform(const std::string &name, const glm::mat4 &matrix)
{
    auto loc = glGetUniformLocation(m_ProgramID, name.data());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::setUniform(const std::string& name, const glm::vec3& vector)
{
    auto loc = glGetUniformLocation(m_ProgramID, name.data());
    glUniform3fv(loc, 1, glm::value_ptr(vector));
}

void Program::setUniform(const std::string& name, float value)
{
    auto loc = glGetUniformLocation(m_ProgramID, name.data());
    glUniform1f(loc, value);
}

void Program::setUniform(const std::string& name, int value)
{
    auto loc = glGetUniformLocation(m_ProgramID, name.data());
    glUniform1i(loc, value);
}

void Program::bind()
{
    glUseProgram(m_ProgramID);
}

void Program::unbind()
{
    glUseProgram(0);
}

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& filename)
{
    int width, height, n;
    unsigned char *data = stbi_load(filename.data(), &width, &height, &n, 0);
    // ... process data if not NULL ...
    // ... x = width, y = height, n = # 8-bit components per pixel ...
    // ... replace '0' with '1'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said 0
    
    if(!data)
    {
        throw std::runtime_error("Error loading texture");
    }
    
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, (GLint)GL_RGB, (GLsizei)width, (GLsizei)height, 0, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<void*>(data));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}



