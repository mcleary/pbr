#pragma once

#include "Shader.h"

class Material
{
public:
	explicit Material();

	virtual void bind() = 0;
	virtual void unbind() = 0;	

	std::shared_ptr<Program> program;
};

class PhongMaterial : public Material
{
public:
	explicit PhongMaterial();

	virtual void bind() override;
	virtual void unbind() override;

	glm::vec3 ambientColor  = { 0.0f, 0.0f, 0.07f };
	glm::vec3 diffuseColor  = { 0.0f, 0.0f, 1.0f };
	glm::vec3 specularColor = { 1.0f, 1.0f, 1.0f };
	GLfloat   shininess		= 32.0f;
	GLfloat   screenGamma   = 2.2f;
};
