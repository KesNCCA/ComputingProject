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
    Asteroid();
    ~Asteroid();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float delta);
    void keyboardPressEvent(const SDL_Event & _event);
    int RandomMovement();
    float GetRadius();
    ngl::Vec3 GetPosition();

    void Damage();
    int GetHealth();
    int GetScoreAmount();


private:
    float m_radius;
    float m_Xdir, m_Ydir;
    int m_health;
    int m_scoreAmount;

};

#endif // ASTEROID_H
