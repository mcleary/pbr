#include "Drawables.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <glbinding/gl/gl.h>

#include <glm/ext.hpp>

void Scene::addDrawable(Drawable* drawable)
{
	m_Drawables.push_back(drawable);
}

void Scene::draw()
{
	for (auto drawable : m_Drawables)
	{
		drawable->draw();
	}
}

#include <iostream>

SphereMesh::SphereMesh(int resolution) :
    m_Resolution(resolution)
{
    const float PI = M_PI;
    const float TWO_PI = 2.0f * M_PI;
    const float INV_RESOLUTION = 1.0f / static_cast<float>(m_Resolution - 1);
    
    for (GLuint uIndex = 0; uIndex < m_Resolution; ++uIndex)
    {
        const float uAlpha = uIndex * INV_RESOLUTION;
        const float theta = glm::mix(0.0f, TWO_PI, uAlpha);
        
        for (GLuint vIndex = 0; vIndex < m_Resolution; ++vIndex)
        {
            const float vAlpha = vIndex * INV_RESOLUTION;
            const float phi = glm::mix(0.0f, PI, vAlpha);
            
            const glm::vec3 vertexPosition =
            {
                std::cos(theta) * std::sin(phi),
                std::sin(theta) * std::sin(phi),
                std::cos(phi)
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
    
    for (GLuint jIndex = 0; jIndex < m_Resolution - 1; ++jIndex)
    {
        for (GLuint iIndex = 0; iIndex < m_Resolution - 1; ++iIndex)
        {
            GLuint i = iIndex;
            GLuint j = jIndex;
            
            GLuint p0 = i   + j     * m_Resolution;
            GLuint p1 = i+1 + j     * m_Resolution;
            GLuint p2 = i   + (j+1) * m_Resolution;
            GLuint p3 = i+1 + (j+1) * m_Resolution;
            
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
    
    std::cout << "Number of triangles: " << m_Indices.size() * 3 *12 << std::endl;

}

void SphereMesh::draw()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size() * 3, GL_UNSIGNED_INT, 0);
    //	glDrawArrays(GL_POINTS, 0, m_Vertices.size());
    glBindVertexArray(0);

}

Sphere::Sphere(glm::vec3 position, float radius, SphereMesh* mesh, Program* program) :
	Drawable(),
	m_Position(position),
	m_Radius(radius),
    m_Mesh(mesh),
    m_Program(program)
{
}

void Sphere::draw()
{
    m_Program->bind();
    auto modelMatrix = glm::translate(m_Position) * glm::scale(glm::vec3(m_Radius));
    m_Program->setUniform("Model", modelMatrix);
    m_Mesh->draw();
    m_Program->unbind();
}
