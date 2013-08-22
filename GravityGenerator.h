#pragma once

#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator();
	GravityGenerator(CL_Vec2f gravity);
	~GravityGenerator(void);

	CL_Vec2f calculate(const Particle& particle) const;
private:
	CL_Vec2f gravity;
};

