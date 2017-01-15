#include "Material.h"

Material::Material()
{
	program = std::make_shared<Program>();
}

PhongMaterial::PhongMaterial() :
	Material()
{
	program->attach(new Shader{ ShaderType::VERTEX, "shaders/phong_vert.glsl" });
	program->attach(new Shader{ ShaderType::FRAGMENT, "shaders/phong_frag.glsl" });
	program->link();
}

void PhongMaterial::bind()
{
	program->bind();
	program->setUniform("DiffuseColor", diffuseColor);
	program->setUniform("SpecularColor", specularColor);
	program->setUniform("AmbientColor", ambientColor);
	program->setUniform("Shininess", shininess);
	program->setUniform("screenGamma", screenGamma);
}

void PhongMaterial::unbind()
{
	program->unbind();
}