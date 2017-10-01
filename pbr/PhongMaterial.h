#pragma once

#include "Material.h"

class PhongMaterial : public Material
{
public:
	explicit PhongMaterial();

	virtual void bind() override;
	virtual void unbind() override;

	glm::vec3 ambientColor	= { 0.0f, 0.0f, 0.07f };
	glm::vec3 diffuseColor	= { 0.0f, 0.0f, 1.0f };
	glm::vec3 specularColor = { 1.0f, 1.0f, 1.0f };
	GLfloat   shininess		= 32.0f;
};
