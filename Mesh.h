#pragma once

#include "Drawable.h"

#include <glm/glm.hpp>

#include <glbinding/Binding.h>
using namespace gl;

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

class Mesh : public Geometry
{
public:
	virtual void draw() override;

protected:

	void initialize(const std::vector<Vertex>& vertices, const std::vector<Triangle>& indices);
	
protected:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_IndicesCount;
};