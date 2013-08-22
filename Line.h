#pragma once

#include "Include.h"
#include "FrictionGenerator.h"

struct Line
{
	CL_LineSegment2f line;
	FrictionGenerator friction;
	float damping;

	Line(const CL_Vec2f& p, const CL_Vec2f& q, const CL_Vec2f& gravity, float friction, float damping) 
		: line(CL_LineSegment2f(p, q)), friction(line.normal(), gravity, friction), damping(damping) {}
};