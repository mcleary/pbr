#pragma once

#include <memory>

#include "Geometry.h"
#include "MaterialParams.h"
#include "Transform.h"

class Drawable
{
public:	
	explicit Drawable(std::shared_ptr<Geometry> mesh);	
	explicit Drawable();

	virtual glm::mat4 modelMatrix() const;

	virtual void draw() = 0;	

	Transform				  transform;	
	MaterialParams			  materialParams;
	std::shared_ptr<Geometry> geometry;
};
