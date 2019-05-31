#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "object.h"
#include <vector>
#include "shot.h"
#include "asteroid.h"

#define INITIAL_HEALTH 100
#define MOVEMENT_AMOUNT 0.2f
#define MOVEMENT_OFFSET 8.0f


//Spaceship inherits from the Object class
class SpaceShip : public Object
{
public:
    SpaceShip();
    ~SpaceShip();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float _delta);
    void keyboardPressEvent(const SDL_Event &_event);
    void Accelerate();
    void setRotation(float _rotAngle);
    void Damage();

    //bullet functions
    void RemoveBullet(int _index);
    std::vector<shot> GetBullets();
    ngl::Vec3 GetPosition();
    int GetNumberOfBullets();
    int GetHealth();

private:

    std::vector<shot> bullets;

    int m_health;
    float m_initialAngle;
    float m_angle;
    float m_prevAngle;
    float m_animationCounter;
    float m_offset;
    float m_acceleration;
    bool isMoving;

};

#endif // SPACESHIP_H
