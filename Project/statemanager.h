#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SDL.h>
#include "NGLDraw.h"

enum {GAME, PAUSED, WINNER};

class StateManager
{
public:
    StateManager(int w, int h);
    ~StateManager();

    void draw();

    void mouseMoveEvent (const SDL_MouseMotionEvent &_event);
    void mousePressEvent (const SDL_MouseButtonEvent &_event);
    void mouseReleaseEvent (const SDL_MouseButtonEvent &_event);
    void wheelEvent(const SDL_MouseWheelEvent &_event);
    void keyboardPressEvent(const SDL_Event &_event);

    void resize(int _w, int _h);

private:
    int state;

    NGLDraw gameState;

};

#endif // STATEMANAGER_H
