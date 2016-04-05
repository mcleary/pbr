#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glbinding/Binding.h>
using namespace gl;

#include "Shader.h"
#include "Camera.h"

class Material
{
public:
    explicit Material();
    
    virtual void bind() = 0;
    virtual void unbind();
};

class SingleProgramMaterial : public Material
{
public:
    SingleProgramMaterial();
    
    Program* program() { return m_Program; }
    
protected:
    Program* m_Program;
};

class SimpleMaterial : public Material
{
public:
    explicit SimpleMaterial();
    
    virtual void bind() override;
};

class SimpleTextureMaterial : public Material
{
public:
    explicit SimpleTextureMaterial(const std::string& filename);
    
    virtual void bind() override;
    virtual void unbind() override;
    
private:
    Texture* m_Texture;
};

class PhongMaterial : public Material
{
public:
    explicit PhongMaterial();
    
    virtual void bind() override;
    
private:
    glm::vec3 m_AmbientColor  = {0.0f, 0.0f, 0.07f};
    glm::vec3 m_DiffuseColor  = {0.0f, 0.0f, 0.7f};
    glm::vec3 m_SpecularColor = {1.0f, 1.0f, 1.0f};
    GLfloat   m_Shininess     = 32.0f;
    GLfloat   m_ScreenGamma   = 2.2f;
};

class EarthMaterial : public Material
{
public:
	explicit EarthMaterial();

	virtual void bind() override;

private:
	Texture* m_EarthTexture;
	Texture* m_CloudsTexture;
	Texture* m_OceanMaskTexture;
	Texture* m_OceanIceTexture;
	Texture* m_EarthNightTexture;	
	Texture* m_EarthTopographyTexture;
};

class AtmosphereMaterial : public Material
{
public:
    explicit AtmosphereMaterial();
    
    virtual void bind() override;
    
private:
    float m_ESun              = 20.0f;
    float m_Kr                = 0.0025f;
    float m_Km                = 0.0010f;
    float m_OutterRadiusScale = 0.25f; // This is going to be the scaling to define the atmosphere thickness
    glm::vec3 m_WaveLength = {0.650f, 0.570f, 0.475f};
};

class PhongPBRMaterial : public Material
{
public:
	explicit PhongPBRMaterial();

	virtual void bind() override;
};

struct Transform
{
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
};

class Drawable
{
public:
    explicit Drawable(Material* material);
    
	virtual void draw() = 0;
	virtual glm::mat4 modelMatrix();
    
    Material* material() { return m_Material; }
	Transform& transform() { return m_Transform; }
    
protected:
	Transform m_Transform;	
    Material* m_Material;
};

class Animator
{
public:
    virtual void update(float deltaTime) = 0;
};

class Light
{
public:
    explicit Light(glm::vec3 position);
    
    glm::vec3& position() { return m_Position; }
private:
    glm::vec3 m_Position;
};

class Scene
{
public:
    explicit Scene();
    
	void addDrawable(Drawable* drawable);
    void addAnimator(Animator* animator);
	void draw();
    void animate(float deltaTime);

	void toggleLightAnimation();	
    
    Camera* camera() { return m_Camera; }
    
private:
	std::vector<Drawable*> m_Drawables;
    std::vector<Animator*> m_Animators;
    Light*                 m_Light;
    Camera*                m_Camera;
	bool			       m_bLightAnimationEnabled = false;
	float				   m_CurrentTime = 0.0f;
};

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

class SphereMesh
{
public:
    explicit SphereMesh(int resolution);  
    
    void draw();    
private:
    GLuint                 m_Resolution;
    std::vector<Vertex>    m_Vertices;
    std::vector<Triangle>  m_Indices;
    
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};

class Sphere : public Drawable
{
public:
    Sphere(glm::vec3 position, float radius, SphereMesh* mesh, Material* material);

	virtual void draw() override;    
private:	
	float		m_Radius;
    SphereMesh* m_Mesh;
};

class SphereAnimator : public Animator
{
public:
    SphereAnimator(Sphere* sphere);
    
    void setRotationSpeed(const glm::vec3& rotVel) { m_RotationVelocity = rotVel; }
    void setTranslationSpeed(const glm::vec3& transVel) { m_TranslationVelocity = transVel; }
    
    virtual void update(float deltaTime) override;
    
private:
    Sphere* m_Sphere;
    
    glm::vec3 m_RotationVelocity;
    glm::vec3 m_TranslationVelocity;
};


