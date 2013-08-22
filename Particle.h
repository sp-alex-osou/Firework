#pragma once

#include "Include.h"

class Particle
{
	friend class Integrator;
	friend class Firework;

public:
	Particle(const CL_Vec2f& position = CL_Vec2f(0, 0), float mass = 1.0f) : position(position), mass(mass) {}
	~Particle(void) {}

	float getMass() const { return mass; }
	const CL_Pointf& getPosition() const { return position; }
	const CL_Vec2f& getVelocity() const { return velocity; }
private:
	CL_Pointf position;
	CL_Vec2f velocity;
	float mass;
};

