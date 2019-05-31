#ifndef MENU_H
#define MENU_H

#include "SDL2/SDL.h"
#include <ngl/Transformation.h>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>

//#include "SDL_ttf.h"



class Menu
{
public:
    Menu();
    ~Menu();

    void draw();

    void resize(int _w, int _h);

    void mousePressEvent (const SDL_MouseButtonEvent &_event);

    void menuLoop();

    void gameText();

private :
//----------------------------------------------------------------------------------------------------------------------
/// @brief method to load transform data to the shaders
//----------------------------------------------------------------------------------------------------------------------
void loadMatricesToShader();
void loadMatricesToShaderAsteroid();

/// @brief Our Camera
//----------------------------------------------------------------------------------------------------------------------
ngl::Mat4 m_view;
ngl::Mat4 m_project;

int m_width;
int m_height;

};

#endif // MENU_H


