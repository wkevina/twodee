#include <twodee.h>

int main()
{
    twodee::System system;
    system.init();

    auto window = system.window();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    twodee::Resource shader_files("res/shaders");

    auto shader = shader_files.load_shader("sprite.vert.glsl", "sprite.frag.glsl");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
