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

	for (float theta = 0; theta <= TWO_PI; theta += TWO_PI / static_cast<float>(m_Resolution))
	{
		for (float phi = 0; phi <= M_PI; phi += M_PI / static_cast<float>(m_Resolution))
		{
			glm::vec3 vertex_position = 
			{
				m_Radius * std::cos(theta) * std::sin(phi),
				m_Radius * std::sin(theta) * std::sin(phi),
                m_Radius * std::cos(theta)
            };
			
            Vertex vertex =
            {
                vertex_position,
                glm::normalize(vertex_position),
                { theta / TWO_PI, phi / M_PI }
            };
            
            m_Vertices.push_back(vertex);
		}
	}	

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    {
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*) (sizeof(glm::vec3)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*) (2 * sizeof(glm::vec3)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }
    glBindVertexArray(0);
}

void Sphere::draw()
{
    glBindVertexArray(m_VAO);
    glPointSize(2.0);
	glDrawArrays(GL_POINTS, 0, m_Vertices.size());
    glBindVertexArray(0);

}
