#include "Axis.h"

AxisGeometry::AxisGeometry(float scale)
{
	const std::vector<LineVertex> Lines = 
	{
		{ { -scale, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
		{ {  scale, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },

		{ { 0.0f, -scale, 0.0f }, {	0.0f, 1.0f, 0.0f } },
		{ { 0.0f,  scale, 0.0f }, {	0.0f, 1.0f, 0.0f } },

		{ { 0.0f, 0.0f, -scale }, { 0.0f, 0.0f, 1.0f } },
		{ { 0.0f, 0.0f,  scale }, { 0.0f, 0.0f, 1.0f } }
	};

	Initialize(Lines);
}

Axis::Axis(float scale) :
	Drawable()
{
	Lines = std::make_shared<AxisGeometry>(scale);
	AxisMaterial = std::make_shared<LinesMaterial>();		
}

void Axis::draw()
{
	AxisMaterial->bind();
	AxisMaterial->bindParams(materialParams);

	Lines->draw();
}