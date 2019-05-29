#ifndef SHOT_H
#define SHOT_H

#include "object.h"

class shot : public Object
{
public:
    shot(ngl::Transformation m_transform, float angle);
    ~shot();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project);
    void keyboardPressEvent(const SDL_Event &_event);

    float angle;

    float GetRadius();
    ngl::Vec3 GetPosition();

private:
    float radius;
};

#endif // SHOT_H
