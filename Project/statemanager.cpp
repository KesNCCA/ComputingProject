#include "statemanager.h"

StateManager::StateManager(int w, int h)
{
    gameState.resize(w, h);

    state = PAUSED;
}

StateManager::~StateManager()
{

}

void StateManager::draw()
{
    if (gameState.GetScore() >= 100)
    {
        state = WINNER;
    }

    switch (state)
    {
    case GAME:
        gameState.draw();

        break;

    case PAUSED:

        break;

    case WINNER:

        std::cout << "Winner winner chicken dinner" << std::endl;

        break;
    }

}

void StateManager::resize(int _w, int _h)
{
    switch (state)
    {
    case GAME:
        gameState.resize(_w, _h);

        break;

    case PAUSED:

        break;

    case WINNER:

        break;
    }
}

void StateManager::mouseMoveEvent (const SDL_MouseMotionEvent &_event)
{
    switch (state)
    {
    case GAME:
        gameState.mouseMoveEvent(_event);

        break;

    case PAUSED:

        break;

    case WINNER:

        break;
    }
}

void StateManager::mousePressEvent (const SDL_MouseButtonEvent &_event)
{
    switch (state)
    {
    case GAME:
        gameState.mousePressEvent(_event);

        break;

    case PAUSED:

        break;

    case WINNER:

        break;
    }
}

void StateManager::mouseReleaseEvent (const SDL_MouseButtonEvent &_event)
{
    switch (state)
    {
    case GAME:
        gameState.mouseReleaseEvent(_event);

        break;

    case PAUSED:

        break;

    case WINNER:

        break;
    }
}

void StateManager::wheelEvent(const SDL_MouseWheelEvent &_event)
{
    switch (state)
    {
    case GAME:
        gameState.wheelEvent(_event);

        break;

    case PAUSED:

        break;

    case WINNER:

        break;
    }
}

void StateManager::keyboardPressEvent(const SDL_Event &_event)
{
    switch( _event.key.keysym.sym )
    {
    // if it's the escape key quit
    case SDLK_p:
        if (state == GAME) { state = PAUSED; }
        else { state = GAME; };
        break;

    default : break;
    } // end of key process

    switch (state)
    {
    case GAME:
        gameState.keyboardPressEvent(_event);

        break;

    case PAUSED:

        break;

    case WINNER:

        break;
    }
}

