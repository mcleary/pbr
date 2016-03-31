#include "Drawables.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <glbinding/gl/gl.h>

#include <glm/ext.hpp>

Material::Material() :
    m_Program(new Program)
{
}

void Material::unbind()
{
    m_Program->unbind();
}

SimpleMaterial::SimpleMaterial() :
    Material()
{
    auto vert = new Shader(ShaderType::VERTEX, "shaders/vertex.glsl");
    auto frag = new Shader(ShaderType::FRAGMENT, "shaders/fragment.glsl");
    
    m_Program->attach(vert);
    m_Program->attach(frag);
    m_Program->link();
};

void SimpleMaterial::bind()
{
    m_Program->bind();
}

PhongMaterial::PhongMaterial() :
    Material()
{
    auto phongVert = new Shader(ShaderType::VERTEX, "shaders/phong_vert.glsl");
    auto phongFrag = new Shader(ShaderType::FRAGMENT, "shaders/phong_frag.glsl");
    
    m_Program->attach(phongVert);
    m_Program->attach(phongFrag);
    m_Program->link();
}

void PhongMaterial::bind()
{
    m_Program->bind();
    m_Program->setUniform("DiffuseColor", m_DiffuseColor);
    m_Program->setUniform("SpecularColor", m_SpecularColor);
    m_Program->setUniform("AmbientColor", m_AmbientColor);
    m_Program->setUniform("Shininess", m_Shininess);
    m_Program->setUniform("Gamma", m_ScreenGamma);
}


Drawable::Drawable(Material* material) :
    m_Material(material)
{
}

Light::Light(glm::vec3 position) :
    m_Position(position)
{
}

Scene::Scene() :
    m_Light(new Light({0.0, 0.0, 10.0})),
    m_Camera(new Camera)
{
}

void Scene::addDrawable(Drawable* drawable)
{
	m_Drawables.push_back(drawable);
}

void Scene::draw()
{
    auto viewMatrix = m_Camera->viewMatrix();
    auto viewProjection = m_Camera->projectionMatrix() * viewMatrix;
    
	for (auto drawable : m_Drawables)
	{
        drawable->material()->bind();
        
        auto modelMatrix = drawable->modelMatrix();
        auto normalMatrix = glm::inverse(glm::transpose(viewMatrix * modelMatrix));
        
        drawable->material()->program()->setUniform("Model", modelMatrix);
        drawable->material()->program()->setUniform("ModelViewProjection", viewProjection * modelMatrix);
        drawable->material()->program()->setUniform("NormalMatrix", normalMatrix);
        drawable->material()->program()->setUniform("lightPos", m_Light->position());
		drawable->draw();
        drawable->material()->unbind();
	}
}

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
            
            Triangle t1{ p3, p2, p0 };
            Triangle t2{ p1, p3, p0 };
            
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

void SphereMesh::draw()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size() * 3, GL_UNSIGNED_INT, 0);
    //	glDrawArrays(GL_POINTS, 0, m_Vertices.size());
    glBindVertexArray(0);

}

Sphere::Sphere(glm::vec3 position, float radius, SphereMesh* mesh, Material* material) :
	Drawable(material),
	m_Position(position),
	m_Radius(radius),
    m_Mesh(mesh)
{
}

void Sphere::draw()
{
    m_Mesh->draw();
}

glm::mat4 Sphere::modelMatrix()
{
    return glm::translate(m_Position) * glm::scale(glm::vec3(m_Radius));
}
