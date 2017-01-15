#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext.hpp>

#include "Mesh.h"
#include "Material.h"
#include "MaterialParams.h"

class Transform
{
public:
	glm::mat4 asMatrix() const;

	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale = glm::vec3(1.0);	
};

class Drawable
{
public:
	explicit Drawable(std::shared_ptr<Mesh> mesh);

	virtual glm::mat4 modelMatrix() const;

	virtual void draw() = 0;	

	Transform				  transform;	
	MaterialParams			  materialParams;
	std::shared_ptr<Mesh>	  mesh;
};
