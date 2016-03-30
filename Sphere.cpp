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
	const float PI = M_PI;
	const float TWO_PI = 2.0f * M_PI;	
	const float INV_RESOLUTION = 1.0f / static_cast<float>(m_Resolution);

	for (int uIndex = 0; uIndex <= m_Resolution; ++uIndex)
	{
		const float uAlpha = uIndex * INV_RESOLUTION;
		const float theta = glm::mix(0.0f, TWO_PI, uAlpha);

		for (int vIndex = 0; vIndex <= m_Resolution; ++vIndex)
		{		
			const float vAlpha = vIndex * INV_RESOLUTION;
			const float phi = glm::mix(0.0f, PI, vAlpha);

			const glm::vec3 vertexPosition =
			{
				m_Radius * std::cos(theta) * std::sin(phi),
				m_Radius * std::sin(theta) * std::sin(phi),
				m_Radius * std::cos(theta)
			};

			Vertex vertex =
			{
				vertexPosition,
				glm::normalize(vertexPosition),
				{ uAlpha, vAlpha }
			};

			m_Vertices.push_back(vertex);			
		}
	}	

	const float numberOfTriangles = 2.0f * (m_Resolution - 1) * (m_Resolution - 1);	
	for (int i = 0; i < m_Resolution + 1; ++i)
	{
		for (int j = 0; j < m_Resolution + 1; ++j)
		{
			GLuint p0 = j + i * m_Resolution;
			GLuint p1 = (j+1) + (i) * m_Resolution;
			GLuint p2 = j + (i + 1) * m_Resolution;
			GLuint p3 = (j + 1) + (i + 1) * m_Resolution;

			Triangle t1{ p0, p2, p3 };
			Triangle t2{ p0, p3, p1 };

			m_Indices.push_back(t1);
			m_Indices.push_back(t2);
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

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(Triangle), m_Indices.data(), GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}

void Sphere::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(m_VAO); 
	glDrawElements(GL_TRIANGLES, m_Indices.size() * sizeof(Triangle), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}
