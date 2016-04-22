#pragma once

#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>
using namespace gl;

#include <glm/glm.hpp>

enum class ShaderType
{
	VERTEX   = static_cast<GLuint>(GL_VERTEX_SHADER),
	TESSCRTL = static_cast<GLuint>(GL_TESS_CONTROL_SHADER),
	TESSEVAL = static_cast<GLuint>(GL_TESS_EVALUATION_SHADER),
	GEOMETRY = static_cast<GLuint>(GL_GEOMETRY_SHADER),
	FRAGMENT = static_cast<GLuint>(GL_FRAGMENT_SHADER),
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
    
    void setUniform(const std::string& name, const glm::mat4& matrix);
    void setUniform(const std::string& name, const glm::vec3& vector);
    void setUniform(const std::string& name, const glm::vec2& vector);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);

    void bind();
    void unbind();

public:
	GLuint m_ProgramID;
};

class Texture
{
public:
    explicit Texture(const std::string& filename);
    
    void bind();
    void unbind();
    
private:
    GLuint m_TextureID;
    int    m_Width;
    int    m_Height;
    int    m_NumberOfComponents;
};

class CubeMap
{
public:
	explicit CubeMap(const std::string& cubemapName);

	void bind();
	void unbind();

private:
	struct FaceInfo
	{
		unsigned char* data = nullptr;
		int width;
		int height;
		int numberOfComponents;
	};

	FaceInfo _loadFaceData(const std::string& basename, const std::string& face);

	GLuint m_CubeMapID;
};