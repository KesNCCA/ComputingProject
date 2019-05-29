#ifndef MENU_H
#define MENU_H

#include "SDL2/SDL.h"
#include <ngl/Transformation.h>
#include <iostream>
//#include "SDL_ttf.h"

class Menu
{
public:
    Menu();
    ~Menu();

    void draw();

    void keyboardPressEvent(const SDL_Event &_event);

    void menuLoop();
    void control();
    void gameText();
};

#endif // MENU_H
