#include "Materials.h"

#include "Shader.h"

#include <glm/ext.hpp>

SimpleMaterial::SimpleMaterial()
{
    m_Program = new Program;
    
    m_Program->attach(new Shader(ShaderType::VERTEX, "shaders/vertex.glsl"));
    m_Program->attach(new Shader(ShaderType::FRAGMENT, "shaders/fragment.glsl"));
    m_Program->link();
}

void SimpleMaterial::bind()
{
    m_Program->bind();
}

void SimpleMaterial::unbind()
{
    m_Program->unbind();
}

SimpleTextureMaterial::SimpleTextureMaterial(const std::string& filename)
{
    m_Program = new Program;
    m_Texture = new Texture(filename);
    
    m_Program->attach(new Shader(ShaderType::VERTEX, "shaders/vertex_texture.glsl"));
    m_Program->attach(new Shader(ShaderType::FRAGMENT, "shaders/fragment_texture.glsl"));
    m_Program->link();
}

void SimpleTextureMaterial::bind()
{
    m_Program->bind();
    
    glActiveTexture(GL_TEXTURE0);
    m_Texture->bind();
    m_Program->setUniform("Texture", 0);
}

void SimpleTextureMaterial::unbind()
{
    m_Texture->unbind();
    m_Program->unbind();
}

PhongMaterial::PhongMaterial()
{
    m_Program = new Program;
    m_Program->attach(new Shader(ShaderType::VERTEX, "shaders/phong_vert.glsl"));
    m_Program->attach(new Shader(ShaderType::FRAGMENT, "shaders/phong_frag.glsl"));
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

void PhongMaterial::unbind()
{
	m_Program->unbind();
}

EarthMaterial::EarthMaterial()
{
    m_Program = new Program;
    m_Program->attach(new Shader(ShaderType::VERTEX, "shaders/ground_from_space_vert.glsl"));
    m_Program->attach(new Shader(ShaderType::FRAGMENT, "shaders/ground_from_space_frag.glsl"));
	//m_Program->attach(new Shader(ShaderType::VERTEX, "shaders/earth_vert.glsl"));
	//m_Program->attach(new Shader(ShaderType::FRAGMENT, "shaders/earth_frag.glsl"));
    m_Program->link();
    
	static const std::string s_TexRes = "2k";

    m_EarthTexture = new Texture("textures/earth_" + s_TexRes + ".jpg");
    m_CloudsTexture = new Texture("textures/earth_clouds_" + s_TexRes + ".jpg");
    m_OceanIceTexture = new Texture("textures/earth_ocean_color_" + s_TexRes + ".jpg");
    m_OceanMaskTexture = new Texture("textures/ocean_mask_" + s_TexRes + ".png");
    m_EarthNightTexture = new Texture("textures/earth_night_" + s_TexRes + ".jpg");
    m_EarthTopographyTexture = new Texture("textures/topography_" + s_TexRes + ".png");
}

void EarthMaterial::bind()
{
    m_Program->bind();
    
    glActiveTexture(GL_TEXTURE0);
    m_EarthTexture->bind();
    
    glActiveTexture(GL_TEXTURE1);
    m_CloudsTexture->bind();
    
    glActiveTexture(GL_TEXTURE2);
    m_OceanMaskTexture->bind();
    
    glActiveTexture(GL_TEXTURE3);
    m_EarthNightTexture->bind();
    
    glActiveTexture(GL_TEXTURE4);
    m_EarthTopographyTexture->bind();
    
    glActiveTexture(GL_TEXTURE5);
    m_OceanIceTexture->bind();
    
    m_Program->setUniform("EarthTexture", 0);
    m_Program->setUniform("CloudsTexture", 1);
    m_Program->setUniform("OceanMaskTexture", 2);
    m_Program->setUniform("NightTexture", 3);
    m_Program->setUniform("TopographyTexture", 4);
    m_Program->setUniform("OceanTexture", 5);
}

void EarthMaterial::unbind()
{
    m_Program->unbind();
}

AtmosphereMaterial::AtmosphereMaterial()
{
    m_Program = new Program;
    
    m_Program->attach(new Shader(ShaderType::VERTEX, "shaders/sky_from_space_vert.glsl"));
    m_Program->attach(new Shader(ShaderType::FRAGMENT, "shaders/sky_from_space_frag.glsl"));
    m_Program->link();
}

void AtmosphereMaterial::bind()
{
    m_Program->bind();
    
    m_Program->setUniform("fKrESun", m_Kr * m_ESun);
    m_Program->setUniform("fKmESun", m_Km * m_ESun);
    m_Program->setUniform("fKr4PI", m_Kr * 4.0f * glm::pi<float>());
    m_Program->setUniform("fKm4PI", m_Km * 4.0f * glm::pi<float>());
    m_Program->setUniform("v3InvWavelength", 1.0f / glm::pow(m_WaveLength, glm::vec3(4)));	
	m_Program->setUniform("fScaleDepth", m_RayleighScaleDepth);
	m_Program->setUniform("g", m_g);
	m_Program->setUniform("g2", m_g * m_g);
}

void AtmosphereMaterial::unbind()
{
	m_Program->unbind();
}