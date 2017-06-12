#include <iostream>
#include <vector>
#include <twodee/twodee.h>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

const int MAX_PARTICLES = 1000;

struct VboWrapper {
    GLuint vbo_id;
    uint64_t buffer_size;
    uint32_t element_size;
    uint32_t element_count;
};

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
        //p.pos = {random_unit_normal(), random_unit_normal()};
    }

    GLuint vbo_id;

    glGenBuffers(1, &vbo_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    auto buf_size = sizeof(twodee::Particle) * MAX_PARTICLES;

    glBufferData(GL_ARRAY_BUFFER, buf_size, particles.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return VboWrapper {vbo_id, buf_size, sizeof(twodee::Particle), MAX_PARTICLES};
}

void limit_framerate(double offset, double frame_length) {
    static double total_time = offset;
    double elapsed_time = offset;

    // reset timer
    glfwSetTime(0);

    using seconds = chrono::duration<double,std::ratio<1>>;

    while (elapsed_time < frame_length) {
        // sleep for remaining time until next frame
        this_thread::sleep_for(seconds(frame_length - elapsed_time));

        // count elapsed time
        elapsed_time += glfwGetTime();
        // reset timer
        glfwSetTime(0);
    }

    total_time += elapsed_time;
}

int main()
{
    twodee::System system;
    system.init();

    auto window = system.window();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    twodee::Resource shader_files("res/shaders");

    auto shader = shader_files.load_shader("sprite.vert.glsl", "sprite.frag.glsl");

    twodee::ParticleSystem particle_system{10000, 10000, glm::vec2(1.0, 1.0)};

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glfwSetTime(0);

        particle_system.update(1.0 / 60);

        /* Render here */
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        /* set up shaders and vertex data */
        shader.activate();

        // shader.validate();

        /* emit render commands */
        //glDrawArrays(GL_POINTS, 0, particle_vbo.element_count);

        particle_system.render();

        /* reset state */
        shader.deactivate();

        //glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        limit_framerate(glfwGetTime(), 1.0 / 60);
    }

    return 0;
}
