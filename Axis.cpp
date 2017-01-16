#include "Axis.h"

Axis::Axis(float scale) :
	Drawable()
{
	AxisMaterial = std::make_shared<LinesMaterial>();
	
	std::array<GLfloat, 36> vertices =
	{
		-scale, 0.0f, 0.0f,	1.0f, 0.0f, 0.0,
		scale, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

		0.0f, -scale, 0.0f,	0.0f, 1.0f, 0.0f,
		0.0f, scale, 0.0f,	0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, -scale,	0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, scale,	0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
}

void Axis::draw()
{
	AxisMaterial->bind();
	AxisMaterial->bindParams(materialParams);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);
}