#pragma once

#include "Particle.h"
#include "Include.h"

class Integrator
{
public:
	Integrator(void);
	~Integrator(void);

	void integrate(Particle& particle, const CL_Vec2f& force, float time) const;
};

