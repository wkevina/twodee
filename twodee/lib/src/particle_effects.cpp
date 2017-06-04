#include "twodee/particle_effects.h"


using namespace twodee;

Particle Emitter::emit_particle() const
{
    return Particle {
            {0.0, 0.0},     // initial position
            _dir * _speed,  // initial velocity
            {0.0, 0.0},     // inital acceleration
            1.0,            // mass
            _default_color, // color
            _radius,        // radius
            _health         // initial health
    };
}

Emitter::Emitter(float speed, glm::vec2 dir, float radius, glm::vec4 color, unsigned int health)
        : _speed(speed), _dir(dir), _radius(radius), _default_color(color), _health(health)
{

}
