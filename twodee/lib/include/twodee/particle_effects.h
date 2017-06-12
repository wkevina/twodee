#ifndef TWODEE_PARTICLE_EFFECTS_H
#define TWODEE_PARTICLE_EFFECTS_H

#include "twodee/twodee.h"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace twodee {

enum ParticleShaderAttributes {
    position = 0,
    size = 1
};

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

struct ParticleVboElement {
    glm::vec2 pos;
    float radius;

    ParticleVboElement() = default;
    ParticleVboElement(glm::vec2 pos, float radius);
    ParticleVboElement(const Particle & p);
};


class Emitter {
public:
    Emitter();
    Emitter(float speed, glm::vec2 dir, float radius, glm::vec4 color, unsigned int health);

    /**
     * @brief generate particle according to this emitter's parameters
     * TODO: use a generating object to vary particle parameters (e.g. driven by random source)
     * @return Particle
     */
    Particle emit_particle() const;

    // initial direction of emitted particles
    glm::vec2 dir;
    // starting speed; dir * speed = velocity
    float speed;
    // default color
    glm::vec4 default_color;
    // default radius
    float radius;
    // starting health
    unsigned int health;
};

class ParticleSystem {
public:
    ParticleSystem(int start, int max, glm::vec2 extents);

    void update(float dt);
    void render();

    Emitter emitter;

    // container for all particles in system
    std::vector<Particle> particles;

    // simulation parameters
    int start;
    int max;
    int current_particles;

    glm::vec2 extents;

    // rendering related variables
    GLuint vao, vbo;
    std::vector<ParticleVboElement> buffer_data;

private:
    void update_gpu_data();

    void init_particles();
};

}


#endif //TWODEE_PARTICLE_EFFECTS_H
