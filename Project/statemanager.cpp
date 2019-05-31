#include "statemanager.h"

StateManager::StateManager(int w, int h)
{
    gameState.resize(w, h);

    m_state = MENU;
}

StateManager::~StateManager()
{

}

void StateManager::draw(int _w, int _h, float _delta)
{
    if (gameState.GetScore() >= 200)
    {
        std::cout << "YOU WIN!" <<std::endl;

        m_state = MENU;
        gameState.ResetScore();
        gameState = NGLDraw();
        gameState.resize(_w, _h);
        //if enter key is pressed, go back to main menu
    }
    if (gameState.teapotHealth() <= 0)
    {
        m_state = MENU;
    }

    switch (m_state)
    {
    case MENU:

        GameMenu.draw();

        break;

    case GAME:

        gameState.draw(_delta);

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
    switch (m_state)
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
    switch (m_state)
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
    switch (m_state)
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
    switch (m_state)
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
    switch (m_state)
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
    //Game state controls
    //pause
    case SDLK_p:
        if (m_state == GAME)
        {
            m_state = PAUSED;
        }
        else if (m_state == PAUSED)
        {
            m_state = GAME;
        };
        break;

        //Start game
    case SDLK_RETURN:
        if (m_state == MENU)
        {
            m_state = GAME;
        }

    default : break;
    } // end of key process

    switch (m_state)
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
