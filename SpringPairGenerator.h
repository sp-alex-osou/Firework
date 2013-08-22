#pragma once

#include "ForceGenerator.h"

class SpringPairGenerator : public ForceGenerator
{
	friend class Firework;

public:
	SpringPairGenerator(void);
	SpringPairGenerator(float length, float coefficient);
	~SpringPairGenerator(void);

	CL_Vec2f calculate(const Particle& particle) const;
	void addPair(const Particle& a, const Particle& b);
private:
	float length;
	float coefficient;
	std::map<const Particle*, const Particle*> pairs;
};