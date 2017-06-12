#include "twodee/particle_effects.h"
#include <random>
#include <iostream>
#include <glm/ext.hpp>


using namespace twodee;
using namespace std;


/*********************
 * Utility functions *
 *********************/

/**
 * @brief Return float randomly sampled from (-1.0, 1.0)
 * @return
 */
float random_unit_normal()
{
    static default_random_engine generator;
    static uniform_real_distribution<float> distribution(-1.0, 1.0);

    return distribution(generator);
}

/**
 * @brief Return vector with random length and direction.
 * @param max_length
 * @param initial_dir
 * @param angular_range
 * @return
 */
glm::vec2 random_vector(float max_length, glm::vec2 initial_dir, float angular_range)
{
    auto vec = glm::rotate(initial_dir, random_unit_normal() * angular_range) * (max_length * random_unit_normal());

    return vec;
}


/**********************
 * ParticleVboElement *
 **********************/

/**
 * @brief Construct ParticleVboElement from Particle
 * @param p
 */
ParticleVboElement::ParticleVboElement(const Particle & p)
        : pos(p.pos), radius(p.radius)
{
}

/**
 * @brief
 * @param pos
 * @param radius
 */
ParticleVboElement::ParticleVboElement(glm::vec2 pos, float radius)
        : pos(pos), radius(radius)
{
}


/***********
 * Emitter *
 ***********/


/**
 * @brief Construct emitter with default properties
 */
Emitter::Emitter()
{
    speed = 0.1;
    dir = {1, 0};
    radius = 1;
    default_color = {1, 1, 1, 1};
    health = 100;
}

/**
 * @brief Construct emitter with arguments
 * @param speed
 * @param dir
 * @param radius
 * @param color
 * @param health
 */
Emitter::Emitter(float speed, glm::vec2 dir, float radius, glm::vec4 color, unsigned int health)
        : speed(speed), dir(dir), radius(radius), default_color(color), health(health)
{

}

/**
 * @brief Create and return particle
 * @return
 */
Particle Emitter::emit_particle() const
{
    Particle p{
            {0.0, 0.0},     // initial position
            dir * speed,  // initial velocity
            {0.0, 0.0},     // inital acceleration
            1.0,            // mass
            default_color, // color
            radius,        // radius
            health         // initial health
    };

    auto vel = random_vector(speed, dir, M_PI * 0.5);
    auto acc = random_vector(0.1, {1.0, 1.0}, M_PI * 0.5);

    p.vel = vel;
    //p.acc = acc;

    return p;
}


/******************
 * ParticleSystem *
 ******************/


/**
 * @brief Create particle system
 * @param start
 * @param max
 * @param extents
 */
ParticleSystem::ParticleSystem(int start, int max, glm::vec2 extents) :
        start(start), max(max), extents(extents), current_particles(start)
{
    particles = vector<Particle>(start);
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

    init_particles();
}

/**
 * @brief Initialize particle collection
 */
void ParticleSystem::init_particles()
{
    for (auto & p: particles) {
        p = emitter.emit_particle();
        glm::vec2 random_position {random_unit_normal(), random_unit_normal()};
        p.pos = random_position;
    }
}

/**
 * @brief Avance simulation by dt seconds
 * @param dt
 */
void ParticleSystem::update(float dt)
{
    for (auto & particle : particles) {
        particle.pos += particle.vel * dt;
        //particle.vel += particle.acc * dt;
    }
}

/**
 * @brief Render particle system. Draws a point for each particle.
 */
void ParticleSystem::render()
{
    update_gpu_data();

    glBindVertexArray(vao);

    glDrawArrays(GL_POINTS, 0, current_particles);

    glBindVertexArray(0);
}

/**
 * @brief Uploads vertex data describing data necessary for rendering the particle system
 */
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
