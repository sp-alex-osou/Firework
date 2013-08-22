#include "DragGenerator.h"


DragGenerator::DragGenerator(void)
{
}


DragGenerator::DragGenerator(float drag) : drag(drag)
{
}


DragGenerator::~DragGenerator(void)
{
}


CL_Vec2f DragGenerator::calculate(const Particle& particle) const
{
	return -particle.getVelocity() * drag;
}