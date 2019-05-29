//#include <SDL.h>
#include "menu.h"

Menu::Menu()
{

}
Menu::~Menu()
{
    std::cout<<"Shutting down SDL";
}

void Menu::draw()
{
    std::cout <<  "Menu selected" << std::endl;
    glClearColor(0.2f, 0.2f, 0.9f, 1.0f); //blue background
}

void Menu::keyboardPressEvent(const SDL_Event &_event)
{
    if(_event.key.keysym.sym == SDLK_KP_ENTER)
    {
        std::cout << "ENTER KEY PRESSED";
    }
}
