#ifndef SHOT_H
#define SHOT_H

#include "object.h"

#define BULLET_SPEED 0.1f

class shot : public Object
{
public:
    shot(ngl::Transformation m_transform, float _angle);
    ~shot();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float delta);
    void keyboardPressEvent(const SDL_Event &_event);

    float GetRadius();
    ngl::Vec3 GetPosition();

private:
    float m_radius;
    float m_angle;
};

#endif // SHOT_H
