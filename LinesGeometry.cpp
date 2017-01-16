#include "LinesGeometry.h"

void LinesGeometry::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, LinesCount);
	glBindVertexArray(0);
}

void LinesGeometry::Initialize(const std::vector<LineVertex>& Lines)
{
	LinesCount = Lines.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, Lines.size() * sizeof(LineVertex), Lines.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
}