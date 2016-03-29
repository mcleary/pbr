#include "Sphere.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <glm/ext.hpp>

#include <glbinding/gl/gl.h>

Sphere::Sphere(glm::vec3 position, float radius, int resolution) :
	Drawable(),
	m_Position(position),
	m_Radius(radius),
	m_Resolution(resolution)
{
	const float TWO_PI = 2.0f * M_PI;

	for (float theta = 0; theta < TWO_PI; theta += TWO_PI / static_cast<float>(m_Resolution))
	{
		for (float phi = 0; phi < M_PI; phi += M_PI / static_cast<float>(m_Resolution))
		{
			glm::vec3 vertex_position = 
			{
				m_Radius * std::cos(theta) * std::sin(phi),
				m_Radius * std::sin(theta) * std::sin(phi),
				m_Radius * std::cos(theta)
			};			
			
			m_Vertices.push_back({ vertex_position, { 0.0, 0.0, 0.0 },{ 0.0, 0.0 } });
		}
	}	

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS, 0, m_Vertices.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
