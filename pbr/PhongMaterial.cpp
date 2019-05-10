#include "PhongMaterial.h"

PhongMaterial::PhongMaterial() :
	Material()
{
	program->attach(new Shader{ ShaderType::VERTEX, "shaders/phong_vert.glsl" });
	program->attach(new Shader{ ShaderType::FRAGMENT, "shaders/phong_frag.glsl" });
	program->link("Phong");
}

void PhongMaterial::bind()
{
	program->bind();
	program->setUniform("DiffuseColor", diffuseColor);
	program->setUniform("SpecularColor", specularColor);
	program->setUniform("AmbientColor", ambientColor);
	program->setUniform("Shininess", shininess);
}

void PhongMaterial::unbind()
{
	program->unbind();
}