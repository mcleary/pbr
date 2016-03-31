#pragma once

#include <vector>
#include <glm/glm.hpp>

#include <glbinding/Binding.h>
using namespace gl;

#include "Shader.h"

class Drawable
{
public:
	virtual void draw() = 0;
};

class Scene
{
public:
	void addDrawable(Drawable* drawable);
	void draw();
private:
	std::vector<Drawable*> m_Drawables;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Triangle
{
	GLuint p0;
	GLuint p1;
	GLuint p2;
};

class SphereMesh : public Drawable
{
public:
    SphereMesh(int resolution);
    ~SphereMesh();
    
    virtual void draw() override;
    
private:
    GLuint                 m_Resolution;
    std::vector<Vertex>    m_Vertices;
    std::vector<Triangle>  m_Indices;
    
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};

class Sphere : public Drawable
{
public:
	Sphere(glm::vec3 position, float radius, SphereMesh* mesh, Program* shaderProgram);

	virtual void draw() override;

private:
	glm::vec3	m_Position;
	float		m_Radius;
    SphereMesh* m_Mesh;
    Program*    m_Program;
};
