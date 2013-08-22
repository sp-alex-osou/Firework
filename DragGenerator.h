#pragma once

#include "ForceGenerator.h"

class DragGenerator : public ForceGenerator
{
public:
	DragGenerator(void);
	DragGenerator(float drag);
	~DragGenerator(void);

	CL_Vec2f calculate(const Particle& particle) const;
private:
	float drag;
};

