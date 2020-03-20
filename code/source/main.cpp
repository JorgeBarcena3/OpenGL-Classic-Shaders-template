
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on february of 2014                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <cassert>
#include <iostream>
#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "../header/exampleShapes/Circle.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"
#include "../header/Shader_Program.hpp"

using namespace sf;
using namespace shaderToolkit;
using namespace std;

void reset_viewport(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GLdouble(width), 0, GLdouble(height), +1, -1);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
}

int main()
{
    int window_width = 800;
    int window_height = 600;

    // Se crea la ventana de SFML, que es donde se creará el contexto de OpenGL:

    Window window(VideoMode(window_width, window_height), "OpenGL Examples: Shader Encapsulation", Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled(true);

    // Una vez se ha creado el contexto de OpenGL ya se puede inicializar Glew:

    GLenum glew_initialization = glewInit();

    assert(glew_initialization == GLEW_OK);

    // Se inicializan diversos aspectos del programa:

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    reset_viewport(window_width, window_height);

    exampleShapes::Circle circle(200.f);

    // Se compilan y se activan los shaders:

    Shader_Program shader_program;

    shader_program.attach(Vertex_Shader(Shader::Source_Code::from_string("../../assets/vertexShader.vglsl")));
    shader_program.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

    shader_program.link();
    shader_program.use();

    bool running = true;

    do
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                running = false;
                break;
            }

            case Event::Resized:
            {
                Vector2u window_size = window.getSize();

                window_width = window_size.x;
                window_height = window_size.y;

                reset_viewport(window_width, window_height);

                break;
            }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(float(window_width / 2), float(window_height / 2), 0.f);

        circle.render();

        window.display();
    } while (running);

    return (EXIT_SUCCESS);
}
