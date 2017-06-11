#include "twodee/particle_effects.h"


using namespace twodee;
using namespace std;

ParticleVboElement::ParticleVboElement(const Particle & p)
        : pos(p.pos), radius(p.radius)
{
}

ParticleVboElement::ParticleVboElement(glm::vec2 pos, float radius)
        : pos(pos), radius(radius)
{

}

Emitter::Emitter()
{
    speed = 1;
    dir = {1, 0};
    radius = 1;
    default_color = {1, 1, 1, 1};
    health = 100;
}

Emitter::Emitter(float speed, glm::vec2 dir, float radius, glm::vec4 color, unsigned int health)
        : speed(speed), dir(dir), radius(radius), default_color(color), health(health)
{

}

Particle Emitter::emit_particle() const
{
    return Particle {
            {0.0, 0.0},     // initial position
            dir * speed,  // initial velocity
            {0.0, 0.0},     // inital acceleration
            1.0,            // mass
            default_color, // color
            radius,        // radius
            health         // initial health
    };
}

ParticleSystem::ParticleSystem(int start, int max, glm::vec2 extents) :
        start(start), max(max), extents(extents), current_particles(0)
{
    particles = vector<Particle>(max);
    buffer_data = vector<ParticleVboElement>(max);

    // generate VBO and VAO
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    // configure VAO
    glBindVertexArray(vao);

    // set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // configure attributes
    // set up position
    glVertexAttribPointer(ParticleShaderAttributes::position, 2, GL_FLOAT, false, sizeof(ParticleVboElement),
                          (void *) offsetof(ParticleVboElement, pos));
    glEnableVertexAttribArray(ParticleShaderAttributes::position);

    // set up size
    glVertexAttribPointer(ParticleShaderAttributes::size, 1, GL_FLOAT, false, sizeof(ParticleVboElement),
                          (void *) offsetof(ParticleVboElement, radius));
    glEnableVertexAttribArray(ParticleShaderAttributes::size);

    // reset vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unset VAO
    glBindVertexArray(0);
}

void ParticleSystem::update(float dt)
{
    update_gpu_data();


}

void ParticleSystem::render()
{

}

void ParticleSystem::update_gpu_data()
{
    // copy attributes from particles collection to particle vertex buffer
    for (int i = 0; i < current_particles; ++i) {
        buffer_data[i] = ParticleVboElement(particles[i]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Send that data to GPU
    glBufferData(GL_ARRAY_BUFFER, current_particles * sizeof(ParticleVboElement), buffer_data.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
