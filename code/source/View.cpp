
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../header/View.hpp"
#include <iostream>
#include <cassert>
#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"

namespace exampleShapes
{

    using namespace std;
 
    View::View(int width, int height)
    :
        cube1("../../assets/tga/wood-crate-1.tga"),
        cube2("../../assets/tga/wood-crate-2.tga"),
        angle(0)
    {
        resize (width, height);

        // Se habilita el backface culling:

        glEnable (GL_CULL_FACE);

        // Se compilan y se activan los shaders:

        shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/vertexShader.vglsl")));
        shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

        shaderProgram.link();
        shaderProgram.use();

    }

    void View::update ()
    {
        angle += 0.5f;
    }

    void View::render ()
    {
        glClear (GL_COLOR_BUFFER_BIT);

        // Resetear la matriz MODELVIEW:

        glLoadIdentity ();

        // Se rota el cubo 1 y se empuja hacia el fondo:

        glTranslatef   (-2.f, 0.f, -20.f);
        glRotatef      (-angle, 1.f, 2.f, 1.f);

        // Se dibuja el cubo 1:

        cube1.render   ();

        // Se rota el cubo 2 y se empuja hacia el fondo:

        glLoadIdentity ();
        glTranslatef   (+2.f, 0.f, -20.f);
        glRotatef      (+angle, 1.f, 2.f, 1.f);

        // Se dibuja el cubo 2:

        cube2.render   ();
    }

    void View::resize (int width, int height)
    {
        glMatrixMode   (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective (20, GLdouble(width) / height, 1, 50);
        glViewport     (0, 0, width, height);
        glClearColor   (0.f, 0.f, 0.f,  1.f);
        glMatrixMode   (GL_MODELVIEW);
    }

}
