#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "object.h"
#include <vector>
#include "shot.h"
#include "asteroid.h"

/*GAME PLAN - each level doubles the amount of asteroids. 2 mins each level.
 Power up that destroys all the ateroids in the vicinity. Highscore */


class SpaceShip : public Object
{
public:
    SpaceShip();
    ~SpaceShip();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project);
    void keyboardPressEvent(const SDL_Event &_event);
    void Accelerate();
    void setRotation(float rotAngle);

    //bullet functions
    void RemoveBullet(int index);
    std::vector<shot> GetBullets();
    ngl::Vec3 GetPosition();
    int GetNumberOfBullets();
    int score;

private:

    std::vector<shot> bullets;

    float initialAngle;
    float angle;
    float prevAngle;
    float animationCounter;
    float offset;
    float acceleration;
    bool isMoving;
    bool keepMoving;

};

#endif // SPACESHIP_H
