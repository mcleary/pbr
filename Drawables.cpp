#include "Drawables.h"

#include <glbinding/gl/gl.h>

#include <glm/ext.hpp>

glm::mat4 Drawable::modelMatrix()
{
	return glm::translate(m_Transform.translation) * glm::toMat4(m_Transform.rotation) * glm::scale(m_Transform.scale);
}

Light::Light(glm::vec3 position) :
    m_Position(position)
{
}

Scene::Scene() :
    m_Light(new Light({0.0, 0.0, 300.0})),
    m_Camera(new Camera)
{
}

void Scene::addDrawable(Drawable* drawable)
{
	m_Drawables.push_back(drawable);
}

void Scene::addAnimator(Animator* animator)
{
    m_Animators.push_back(animator);
}

void Scene::draw()
{
    auto viewMatrix = m_Camera->viewMatrix();	
    auto viewProjection = m_Camera->projectionMatrix() * viewMatrix;
    
//    static Sphere* lightSphere = nullptr;
//    if(!lightSphere)
//    {
//        lightSphere = new Sphere(m_Light->position(), 0.5f, new SphereMesh(10), new SimpleMaterial);
//    }
    
//    lightSphere->transform().translation = m_Light->position();
//    lightSphere->material()->bind();
//    lightSphere->material()->program()->setUniform("ModelViewProjection", viewProjection * lightSphere->modelMatrix());
//    lightSphere->material()->program()->setUniform("NormalMatrix", glm::transpose(glm::inverse(viewMatrix * lightSphere->modelMatrix())));
    //lightSphere->draw();
//    lightSphere->material()->unbind();
    
	glm::vec4 lightViewPos = viewMatrix * glm::vec4{ m_Light->position(), 1.0f };	
    
	for (auto drawable : m_Drawables)
	{
		auto modelMatrix = drawable->modelMatrix();
		auto modelViewMatrix = viewMatrix * modelMatrix;
		auto normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

		drawable->matParams().set("Gamma", m_Gamma);
		drawable->matParams().set("Time", m_CurrentTime);
		drawable->matParams().set("Model", modelMatrix);
		drawable->matParams().set("View", viewMatrix);
		drawable->matParams().set("ViewProjection", viewProjection);
		drawable->matParams().set("ModelView", modelViewMatrix);
		drawable->matParams().set("ModelViewProjection", viewProjection * modelMatrix);
		drawable->matParams().set("NormalMatrix", normalMatrix);		
		
		drawable->matParams().set("CameraWorldPos", m_Camera->eye());		
		drawable->matParams().set("fCameraHeight", glm::length(m_Camera->eye()));
		drawable->matParams().set("fCameraHeight2", glm::length2(m_Camera->eye()));

		auto lightViewDir = viewMatrix * glm::vec4{ m_Light->position() - drawable->transform().translation, 0.0f };
		drawable->matParams().set("LightPos", glm::vec3{ lightViewPos } / lightViewPos.w);
		drawable->matParams().set("LightWorldPos", m_Light->position());
		drawable->matParams().set("LightDir", glm::normalize((glm::vec3{ lightViewDir })));
		drawable->matParams().set("LightWorldDir", glm::normalize(m_Light->position() - drawable->transform().translation));

		drawable->draw();
	}
}

void Scene::animate(float deltaTime)
{
	m_CurrentTime += deltaTime;

    static float LightRotationSpeed = -0.04f;
	if (m_bLightAnimationEnabled)
	{
		m_Light->position() = glm::rotateY(m_Light->position(), LightRotationSpeed * deltaTime);
	}
    
    for(auto animator : m_Animators)
    {
        animator->update(deltaTime);
    }

	m_Camera->update(deltaTime);
}

void Scene::toggleLightAnimation()
{
	m_bLightAnimationEnabled = !m_bLightAnimationEnabled;
}

SphereMesh::SphereMesh(int resolution) :
    m_Resolution(resolution)
{
    const float PI = glm::pi<float>();
    const float TWO_PI = glm::two_pi<float>();
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
                { 1.0 - uAlpha, 1.0 - vAlpha }
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
	m_Radius(radius),
    m_Mesh(mesh),
	m_Material(material)
{
	transform().translation = position;
	transform().scale = glm::vec3(m_Radius);
}

void Sphere::draw()
{
	m_Material->bind();
	matParams().bindToMaterial(m_Material);
    m_Mesh->draw();
	m_Material->unbind();
}

SphereAnimator::SphereAnimator(Sphere* sphere) :
    Animator(),
    m_Sphere(sphere)
{
}

void SphereAnimator::update(float deltaTime)
{
	auto& translation = m_Sphere->transform().translation;
	auto& rotation = m_Sphere->transform().rotation;
    
    translation += m_TranslationVelocity * deltaTime;
    rotation *= glm::quat(m_RotationVelocity * deltaTime);
}

Earth::Earth(float radius) :
	m_Radius(radius),
	m_Mesh(new SphereMesh(200)),
	m_EarthMaterial(new EarthMaterial),
	m_AtmosphereMaterial(new AtmosphereMaterial)
{		
	transform().translation = glm::vec3(0.0);
	transform().scale = glm::vec3(m_Radius);
	transform().rotation = glm::vec3(glm::radians(90.0f), 0.0f, 0.0f);

	m_OuterRadius = m_Radius * 1.025;
}

void Earth::draw()
{	
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_EarthMaterial->bind();
	{
		matParams().bindToMaterial(m_EarthMaterial);

		//
		// TODO: Needs serious refactoring
		//
		auto p = m_EarthMaterial->program();

		p->setUniform("fOuterRadius", m_OuterRadius);
		p->setUniform("fOuterRadius2", m_OuterRadius * m_OuterRadius);
		p->setUniform("fInnerRadius", m_Radius);
		p->setUniform("fScale", 1.0f / (m_OuterRadius - m_Radius));
		p->setUniform("fScaleOverScaleDepth", (1.0f / (m_OuterRadius - m_Radius)) / m_AtmosphereMaterial->m_RayleighScaleDepth);
		p->setUniform("fKrESun", m_AtmosphereMaterial->m_Kr * m_AtmosphereMaterial->m_ESun);
		p->setUniform("fKmESun", m_AtmosphereMaterial->m_Km * m_AtmosphereMaterial->m_ESun);
		p->setUniform("fKr4PI", m_AtmosphereMaterial->m_Kr * 4.0f * glm::pi<float>());
		p->setUniform("fKm4PI", m_AtmosphereMaterial->m_Km * 4.0f * glm::pi<float>());
		p->setUniform("v3InvWavelength", 1.0f / glm::pow(m_AtmosphereMaterial->m_WaveLength, glm::vec3(4)));
		p->setUniform("fScaleDepth", m_AtmosphereMaterial->m_RayleighScaleDepth);

		m_Mesh->draw();
	}	
	m_EarthMaterial->unbind();

	glFrontFace(GL_CW);
	glBlendFunc(GL_ONE, GL_ONE);

	m_AtmosphereMaterial->bind();
	{	
		matParams().bindToMaterial(m_AtmosphereMaterial);
		m_AtmosphereMaterial->program()->setUniform("fOuterRadius", m_OuterRadius);
		m_AtmosphereMaterial->program()->setUniform("fOuterRadius2", m_OuterRadius * m_OuterRadius);
		m_AtmosphereMaterial->program()->setUniform("fInnerRadius", m_Radius);
		m_AtmosphereMaterial->program()->setUniform("fScale", 1.0f / (m_OuterRadius - m_Radius));
		m_AtmosphereMaterial->program()->setUniform("fScaleOverScaleDepth", (1.0f / (m_OuterRadius - m_Radius)) / m_AtmosphereMaterial->m_RayleighScaleDepth);		
		m_Mesh->draw();
	}	
	m_AtmosphereMaterial->unbind();
}
