#pragma once

#include "ForceGenerator.h"

class SpringGenerator : public ForceGenerator
{
	friend class Firework;

public:
	SpringGenerator(void);
	SpringGenerator(const CL_Vec2f& position, float length, float coefficient);
	~SpringGenerator(void);

	CL_Vec2f calculate(const Particle& particle) const;
private:
	CL_Vec2f position;
	float length;
	float coefficient;
};

