#ifndef TWODEE_PARTICLE_EFFECTS_H
#define TWODEE_PARTICLE_EFFECTS_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace twodee {

/**
 * @brief Particle: object that moves through space, expiring after some time
 */
struct Particle {
    using vec_type = glm::vec2;
    // particle position
    glm::vec2 pos;
    // particle velocity
    glm::vec2 vel;
    // acceleration
    glm::vec2 acc;
    // mass
    float mass;
    // color
    glm::vec4 color;
    // rendering size of particle
    float radius;
    // lifetime of particle, expressed as number of iterations left to live
    unsigned int health;
};

class Emitter {
private:
    // initial direction of emitted particles
    glm::vec2 _dir;
    // starting speed; dir * speed = velocity
    float _speed;
    // default color
    glm::vec4 _default_color;
    // default radius
    float _radius;
    // starting health
    unsigned int _health;

public:
    Emitter(float speed, glm::vec2 dir, float radius, glm::vec4 color, unsigned int health);

    /**
     * @brief generate particle according to this emitter's parameters
     * TODO: use a generating object to vary particle parameters (e.g. driven by random source)
     * @return Particle
     */
    Particle emit_particle() const;
};


}


#endif //TWODEE_PARTICLE_EFFECTS_H
