#pragma once

#include <vector>
#include <glm/glm.hpp>

#include <glbinding/Binding.h>
using namespace gl;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Drawable
{
public:
	virtual void draw() = 0;
};

class Sphere : public Drawable
{
public:
	Sphere(glm::vec3 position, float radius, int resolution);

	virtual void draw() override;

private:
	glm::vec3	m_Position;
	float		m_Radius;
	int			m_Resolution;

	std::vector<Vertex>    m_Vertices;
	std::vector<int>       m_Indices;

    GLuint m_VAO;
	GLuint m_VBO;
};