#include "SpringPairGenerator.h"


SpringPairGenerator::SpringPairGenerator(void)
{
}


SpringPairGenerator::SpringPairGenerator(float length, float coefficient)
	: length(length), coefficient(coefficient)
{
}


SpringPairGenerator::~SpringPairGenerator(void)
{
}


void SpringPairGenerator::addPair(const Particle& a, const Particle& b)
{
	pairs[&a] = &b;
	pairs[&b] = &a;
}


CL_Vec2f SpringPairGenerator::calculate(const Particle& particle) const
{
	std::map<const Particle*, const Particle*>::const_iterator it = pairs.find(&particle);

	if (it == pairs.end())
		return 0;

	CL_Vec2f d = it->second->getPosition() - particle.getPosition();

	return CL_Vec2f::normalize(d) * (d.length() - length) * coefficient;
}