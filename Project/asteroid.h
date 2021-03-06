#ifndef ASTEROID_H
#define ASTEROID_H

#include "object.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

#define INITIAL_HEALTH 2
#define INITIAL_SCORE 30
#define MOVEMENT_AMOUNT 0.5f
#define _RADIUS_ 0.5

class Asteroid : public Object
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor
    //----------------------------------------------------------------------------------------------------------------------
    Asteroid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor
    //----------------------------------------------------------------------------------------------------------------------
    ~Asteroid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Drawing asteroid (called within NGLDraw.cpp)
    //----------------------------------------------------------------------------------------------------------------------
    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float delta);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Keyboard event handling
    //----------------------------------------------------------------------------------------------------------------------
    void keyboardPressEvent(const SDL_Event & _event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Random position and movement of asteroids
    //----------------------------------------------------------------------------------------------------------------------
    int RandomMovement();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns radius of asteroids (for collision)
    //----------------------------------------------------------------------------------------------------------------------
    float GetRadius();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns a vector of the current position of asteroids (for collision)
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 GetPosition();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief damages asteroid (used within collision detection)
    //----------------------------------------------------------------------------------------------------------------------
    void Damage();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns health of asteroid
    //----------------------------------------------------------------------------------------------------------------------
    int GetHealth();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns game score
    //----------------------------------------------------------------------------------------------------------------------
    int GetScoreAmount();

private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief asteroid radius
    //----------------------------------------------------------------------------------------------------------------------
    float m_radius;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief asteroid x and y directions (x and z)
    //----------------------------------------------------------------------------------------------------------------------
    float m_Xdir, m_Ydir;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief asteroids health
    //----------------------------------------------------------------------------------------------------------------------
    int m_health;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief game score
    //----------------------------------------------------------------------------------------------------------------------
    int m_scoreAmount;

};

#endif // ASTEROID_H
