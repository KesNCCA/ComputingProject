#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SDL.h>
#include "NGLDraw.h"
#include "menu.h"

enum {GAME, PAUSED, WINNER, LOSER, MENU};

class StateManager
{
public:
    StateManager(int w, int h);
    ~StateManager();

    void draw(int _w, int _h, float _delta);

    void mouseMoveEvent (const SDL_MouseMotionEvent &_event);
    void mousePressEvent (const SDL_MouseButtonEvent &_event);
    void mouseReleaseEvent (const SDL_MouseButtonEvent &_event);
    void wheelEvent(const SDL_MouseWheelEvent &_event);
    void keyboardPressEvent(const SDL_Event &_event);

    void resize(int _w, int _h);

    void changeState();

private:

    NGLDraw gameState;
    Menu GameMenu;

    int m_state;

};

#endif // STATEMANAGER_H
