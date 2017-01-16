#pragma once

#include "Drawable.h"
#include "LinesMaterial.h"

class Axis : public Drawable
{
public:
	explicit Axis(float scale = 100.0f);

	virtual void draw() override;

private:
	std::shared_ptr<LinesMaterial> AxisMaterial;

	GLuint VAO;
	GLuint VBO;
};