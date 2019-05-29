#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <ngl/Transformation.h>
#include <ngl/Mat4.h>
#include <ngl/Vec3.h>
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>

class Object
{
public:
    Object();
    ~Object();

    void Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project);
    void keyboardPressEvent(const SDL_Event &_event);

protected:
    void loadMatricesToShader(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project);

    ngl::Transformation m_transform;
    ngl::Transformation m_rotate;

    float HeightPos;
    float xDirection;
    float yDirection;
    float zDirection;
};

#endif // OBJECT_H
