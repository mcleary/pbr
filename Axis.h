#pragma once

#include "Drawable.h"
#include "LinesMaterial.h"
#include "LinesGeometry.h"

class AxisGeometry : public LinesGeometry
{
public:
	explicit AxisGeometry(float scale);

};

class Axis : public Drawable
{
public:
	explicit Axis(float scale = 100.0f);

	virtual void draw() override;

private:
	std::shared_ptr<AxisGeometry>  Lines;
	std::shared_ptr<LinesMaterial> AxisMaterial;
};