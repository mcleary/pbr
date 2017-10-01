#pragma once

#include "Geometry.h"

#include <glm/glm.hpp>

#include <glbinding/gl/gl.h>
using namespace gl;

#include <vector>

struct LineVertex
{
	glm::vec3 Position;
	glm::vec3 Color;
};

class LinesGeometry : public Geometry
{
public:
	virtual void draw() override;

protected:
	void Initialize(const std::vector<LineVertex>& Lines);

private:
	GLuint LinesCount;
	GLuint VAO;
	GLuint VBO;
};