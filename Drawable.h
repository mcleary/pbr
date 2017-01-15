#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext.hpp>

#include "Mesh.h"

struct Transform
{
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale = glm::vec3(1.0);
};

class Drawable
{
public:
	explicit Drawable(std::shared_ptr<Mesh> mesh);

	virtual void draw();
	
	virtual glm::mat4 modelMatrix() const;

	Transform& transform();

private:
	Transform			  m_Transform;
	std::shared_ptr<Mesh> m_Mesh;
};
