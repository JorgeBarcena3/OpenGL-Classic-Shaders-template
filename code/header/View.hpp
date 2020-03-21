
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Cube.hpp"
#include <string>
#include "Shader_Program.hpp"

namespace exampleShapes
{

    using namespace shaderToolkit;

    class View
    {
    private:

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        Cube   cube1;
        Cube   cube2;
        float  angle;

    public:

        View(int width, int height);

        void   update();
        void   render();
        void   resize(int width, int height);

    private:

        Shader_Program shaderProgram;
    };

}

#endif
