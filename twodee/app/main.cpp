#include <iostream>
#include <vector>
#include <twodee/twodee.h>
#include <random>

using namespace std;

const int MAX_PARTICLES = 1000;

struct VboWrapper {
    GLuint vbo_id;
    uint64_t buffer_size;
    uint32_t element_size;
    uint32_t element_count;
};


float random_unit_normal() {
    static default_random_engine generator;
    static uniform_real_distribution<float> distribution(-1.0, 1.0);

    return distribution(generator);
}

VboWrapper load_particle_vbo() {
    twodee::Emitter emitter {
            1.0,
            {1.0, 0.0},
            1.0,
            {1.0 ,1.0, 1.0, 1.0},
            1000
    };

    vector<twodee::Particle> particles(MAX_PARTICLES);

    for (twodee::Particle & p: particles) {
        p = emitter.emit_particle();
        p.pos = {random_unit_normal(), random_unit_normal()};
    }

    GLuint vbo_id;

    glGenBuffers(1, &vbo_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    auto buf_size = sizeof(twodee::Particle) * MAX_PARTICLES;

    glBufferData(GL_ARRAY_BUFFER, buf_size, particles.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return VboWrapper {vbo_id, buf_size, sizeof(twodee::Particle), MAX_PARTICLES};
}

int main()
{
    cout << "Particle is standard layout type: " << is_standard_layout<twodee::Particle>() << endl;
    cout << "vec2 length is: " << glm::vec2::length() << endl;

    twodee::System system;
    system.init();

    auto window = system.window();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    twodee::Resource shader_files("res/shaders");

    auto shader = shader_files.load_shader("sprite.vert.glsl", "sprite.frag.glsl");

    auto particle_vbo = load_particle_vbo();

    int buf_size;

    glBindBuffer(GL_ARRAY_BUFFER, particle_vbo.vbo_id);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buf_size);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cout << "Buffer size is: " << buf_size << endl;

    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);

    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, particle_vbo.vbo_id);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(twodee::Particle), (const void *)0);   //offsetof(twodee::Particle, pos));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* set up shaders and vertex data */
        shader.activate();
        glBindVertexArray(vao_id);

        /* emit render commands */
        glDrawArrays(GL_POINTS, 0, particle_vbo.element_count);

        /* reset state */
        shader.deactivate();
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
