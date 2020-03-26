
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by �ngel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

#include "ExampleShape.hpp"

namespace exampleShapes
{

    class Circle : public ExampleShape
    {
    private:

        GLuint display_list_id;

    public:

        Circle(float radius)
        {
            create_display_list(radius);
        }

        ~Circle()
        {
            glDeleteLists(display_list_id, 1);
        }

        void render() override
        {
            glCallList(display_list_id);
        }

    private:

        void create_display_list(float radius)
        {
            // Se crea una lista y se guarda su identificador:

            display_list_id = glGenLists(1);

            // Se compilan los comandos que dibujan el c�rculo en la lista:

            glNewList(display_list_id, GL_COMPILE);
            {
                // Se dibuja el c�rculo con coordenadas locales de v�rtices cacheadas:

                glBegin(GL_TRIANGLE_FAN);
                {
                    // Se a�ade el primer v�rtice en el centro:

                    glVertex2f(0, 0);

                    // Se a�aden v�rtices sobre el borde del c�rculo:

                    for (float angle = 0.f; angle < 6.283185f; angle += 0.05f)
                    {
                        glVertex2f(std::cosf(angle) * radius, std::sinf(angle) * radius);
                    }

                    // Se a�ade un �ltimo v�rtice de cierre donde angle vale 0

                    glVertex2f(radius, 0);
                }
                glEnd();
            }
            glEndList();
        }

    };

}

#endif
