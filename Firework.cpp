#include "Firework.h"

Firework::Firework(Game& game) : GameComponent(game), total(0.0f), hasExploded(false)
{
}


Firework::~Firework(void)
{
}


void Firework::init()
{
	const CL_Vec2f g = CL_Vec2f(0, -100);
	const float friction = 0.1f;
	const float damping = 0.4f;



	lines.push_back(Line(CL_Vec2f(-350, 200), CL_Vec2f(-20, 100), g, friction, damping));
	lines.push_back(Line(CL_Vec2f(350, 400), CL_Vec2f(20, 100), g, friction, damping));
	lines.push_back(Line(CL_Vec2f(20, 50), CL_Vec2f(20, 100), g, friction, damping));
	lines.push_back(Line(CL_Vec2f(-20, 100), CL_Vec2f(-20, 50), g, friction, damping));
	lines.push_back(Line(CL_Vec2f(-100, 400), CL_Vec2f(150, 300), g, friction, damping));

	CL_Vec2f corners[4] = { CL_Vec2f(350, 50), CL_Vec2f(350, 550), CL_Vec2f(-350, 550), CL_Vec2f(-350, 50) };

	for (int i = 0; i < 3; ++i)
		lines.push_back(Line(corners[i], corners[i+1], g, friction, damping));

	gravity = GravityGenerator(g);
	engine = ThrustGenerator(800, CL_Vec2f(0, 1));
	explosion = ThrustGenerator(20000);
	drag = DragGenerator(0.1f);
	spring = SpringGenerator(CL_Vec2f(-250, 300), 100, 100);
	springPair = SpringPairGenerator(100, 100);

	for (int i = 0; i < 100; ++i)
	//for (int i = 0; i < 1; ++i)
		particles.push_back(Particle(CL_Vec2f(0, 0), 1));

	//springPair.addPair(particles[0], particles[1]);

	for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		registry.subscribe(*it, gravity);
		registry.subscribe(*it, drag);
		registry.subscribe(*it, engine);
	}
}


void Firework::update(float elapsed)
{
	total += elapsed;

	const float startTime = 1.0f;
	const float explosionTime = 3.0f;

	if (total > startTime)
	{
		for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
			registry.unsubscribe(*it, engine);

		if (total > explosionTime && !hasExploded)
		{
			for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
			{
				registry.subscribe(*it, explosion);
				registry.subscribe(*it, springPair);
				//registry.subscribe(*it, spring);
			}

			for (unsigned i = 0; i < particles.size() / 2; ++i)
				registry.subscribe(particles[i], spring);

			hasExploded = true;
		}
	}

	for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		Particle& particle = *it;

		std::list<const ForceGenerator*> forceGenerators = registry.getForceGenerators(particle);
		CL_Vec2f force;
		
		for (std::list<const ForceGenerator*>::iterator it = forceGenerators.begin(); it != forceGenerators.end(); ++it)
			force += (*it)->calculate(particle);

		CL_Vec2f prevPosition = particle.getPosition();

		integrator.integrate(particle, force, elapsed);

		// particle is not sliding
		if (slides.find(&particle) == slides.end())
		{
			bool collision; 

			std::pair<CL_Vec2f, const Line*> result = checkCollision(prevPosition, particle, lines, collision);

			if (collision)
			{
				CL_Vec2f intersection = result.first;
				const Line* line = result.second;

				CL_Vec2f direction = CL_Vec2f::rotate(line->line.normal(), 0, CL_Angle::from_degrees(90));

				if (direction.y > 0)
					direction *= -1;

				float cos = CL_Vec2f::dot(CL_Vec2f::normalize(particle.velocity), direction);

				// bouncing
				if (line->line.normal().y == 0 || (cos < 0.95f && particle.velocity.length() > 1.0f))
				{
					particle.position = intersection + reflect(intersection - particle.getPosition(), line->line.normal());
					particle.velocity = reflect(-particle.velocity, line->line.normal()) * (1.0f - line->damping);
				}
				// sliding
				else
				{
					particle.position = intersection;
					particle.velocity = direction * particle.velocity.length() * cos;

					registry.subscribe(particle, line->friction);
					registry.unsubscribe(particle, gravity);
					slides[&particle] = line;
				}
			}
		}
		// particle is sliding
		else
		{
			const Line* line = slides[&particle];

			CL_Vec2f p = particle.getPosition();
			CL_Vec2f n = line->line.normal();

			if (!line->line.intersects(CL_LineSegment2f(p - n, p + n), true))
			{
				registry.subscribe(particle, gravity);
				registry.unsubscribe(particle, line->friction);
				slides.erase(&particle);
			}
		}
	}

	if (hasExploded) 
	{
		for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
			registry.unsubscribe(*it, explosion);
	}
}


std::pair<CL_Vec2f, const Line*> Firework::checkCollision(const CL_Vec2f& prevPosition, Particle& particle, const std::list<Line>& lines, bool& collision) const
{
	bool intersects;

	for (std::list<Line>::const_iterator it = lines.begin(); it != lines.end(); ++it)
	{
		CL_Vec2f intersection = it->line.get_intersection(CL_LineSegment2f(prevPosition, particle.getPosition()), intersects);

		collision = intersects;

		if (collision)
			return std::pair<CL_Vec2f, const Line*>(intersection, &(*it));
	}

	return std::pair<CL_Vec2f, const Line*>();
}


CL_Vec2f Firework::reflect(const CL_Vec2f& vector, const CL_Vec2f& normal) const
{
	return normal * 2 * CL_Vec2f::dot(normal, vector) - vector;
}


void Firework::draw(float elapsed)
{
	for (unsigned i = 0; i < particles.size(); ++i)
	{
		CL_Pointf position = scale(particles[i].getPosition());
		CL_Draw::fill(window.get_gc(), position, position - CL_Pointf(3, 3), CL_Colorf::white);
	}

	for (std::list<Line>::iterator it = lines.begin(); it != lines.end(); ++it)
		CL_Draw::line(window.get_gc(), CL_LineSegment2f(scale(it->line.p), scale(it->line.q)), CL_Colorf::white);

	CL_Draw::fill(window.get_gc(), scale(spring.position), scale(spring.position) - CL_Pointf(5, 5), CL_Colorf::red);
}


CL_Vec2f Firework::scale(const CL_Vec2f& v) const
{
	CL_Vec2f scaled;

	CL_Rect viewport = window.get_viewport();

	scaled.x = v.x + viewport.get_width() / 2.0f;
	scaled.y = viewport.get_height() - v.y;
	
	return scaled;
}