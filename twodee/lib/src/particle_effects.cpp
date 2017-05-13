#include "particle_effects.h"


using namespace twodee;

Particle Emitter::emit() const
{
    return Particle {
            {0.0, 0.0}, // initial positon
            _dir * _speed,
            _default_color,
            _radius,
            _health
    };
}

Emitter::Emitter(float speed, glm::vec2 dir, float radius, glm::vec4 color, unsigned int health)
        : _speed(speed), _dir(dir), _radius(radius), _default_color(color), _health(health)
{

}
