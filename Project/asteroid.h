#ifndef ASTEROID_H
#define ASTEROID_H

#include "object.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

#define INITIAL_HEALTH 2
#define INITIAL_SCORE 30

class Asteroid : public Object
{
public:
    Asteroid();
    ~Asteroid();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project);
    void keyboardPressEvent(const SDL_Event &_event);
    int RandomMovement();
    float GetRadius();
    ngl::Vec3 GetPosition();

    void Damage();
    int GetHealth();
    int GetScoreAmount();


private:
    float radius;
    float x, y;
    int health;
    int scoreAmount;

};

#endif // ASTEROID_H
