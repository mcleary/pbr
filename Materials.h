#pragma once

#include <map>

#include <glm/glm.hpp>

#include <string>

#include <glbinding/Binding.h>
using namespace gl;

class Program;
class Texture;

class Material
{
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;

	Program* program() { return m_Program; }

protected:
	Program* m_Program;
};

class SimpleMaterial : public Material
{
public:
    explicit SimpleMaterial();
    
    virtual void bind() override;
    virtual void unbind() override;
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
    virtual void unbind() override;
    
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
    virtual void unbind() override;
    
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
	virtual void unbind() override;
    
private:
    float m_ESun              = 20.0f;
    float m_Kr                = 0.0025f;
    float m_Km                = 0.0010f;
    float m_OutterRadiusScale = 0.25f; // This is going to be the scaling to define the atmosphere thickness
    glm::vec3 m_WaveLength = {0.650f, 0.570f, 0.475f};
};