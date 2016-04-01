#pragma once

#include <vector>
#include <glm/glm.hpp>

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

class PhongMaterial : public Material
{
public:
    explicit PhongMaterial();
    
    virtual void bind() override;
    
private:
    glm::vec3 m_AmbientColor  = {0.0f, 0.0f, 0.07f};
    glm::vec3 m_DiffuseColor  = {0.0f, 0.0f, 0.7f};
    glm::vec3 m_SpecularColor = {1.0f, 1.0f, 1.0f};
    GLfloat   m_Shininess     = 16.0f;
    GLfloat   m_ScreenGamma   = 2.2f;
};

class PhongPBRMaterial : public Material
{
public:
	explicit PhongPBRMaterial();

	virtual void bind() override;
};

class Drawable
{
public:
    explicit Drawable(Material* material);
    
	virtual void draw() = 0;
    virtual glm::mat4 modelMatrix() { return glm::mat4(); }
    
    Material* material() { return m_Material; }
    
protected:
    Material* m_Material;
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
	void draw();
    void animate(float deltaTime);

	void toggleLightAnimation();	
    
    Camera* camera() { return m_Camera; }
    
private:
	std::vector<Drawable*> m_Drawables;
    Light*                 m_Light;
    Camera*                m_Camera;
	bool			       m_bLightAnimationEnabled = false;
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
    
    virtual glm::mat4 modelMatrix() override;

private:
	glm::vec3	m_Position;
	float		m_Radius;
    SphereMesh* m_Mesh;
};
