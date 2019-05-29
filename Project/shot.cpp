#include "shot.h"

#define BULLET_SPEED 0.1f

shot::shot(ngl::Transformation m_transform, float angle)
{
    this->m_transform = m_transform;
    this->angle = angle;

    radius = 0.2f;
}

shot::~shot(){}

void shot::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project)
{

    ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

    //low poly sphere (bullets)
    prim->createSphere("sphere",radius, 1);

    bool isSwitchingSides = false;

    //bullet moves in the direction that the ship is moving
    float x = (float) sin((float)(m_transform.getRotation().m_y + angle) * ngl::PI / 180.0f)*BULLET_SPEED;
    float y = (float) cos((float)(m_transform.getRotation().m_y + angle) * ngl::PI / 180.0f)*BULLET_SPEED;

    if (m_transform.getPosition().m_x >= 10 || m_transform.getPosition().m_x <= -10)
    {
        isSwitchingSides = true;
    }
    if (m_transform.getPosition().m_z >= 10 || m_transform.getPosition().m_z <= -10)
    {
        isSwitchingSides = true;
    }

    if (isSwitchingSides)
    {
        //remove from vector
        m_transform.setPosition(m_transform.getPosition().m_x * -1.0f, HeightPos, m_transform.getPosition().m_z * -1.0f);
        isSwitchingSides = false;
    }

    //prevAngle = m_transform.getRotation().m_y;
    m_transform.addPosition(x, 0.0, y);

    loadMatricesToShader(m_view, m_mouseGlobalTX, m_project);
    prim->draw( "sphere" );
}

float shot::GetRadius()
{
    return radius;
}

ngl::Vec3 shot::GetPosition()
{
    return m_transform.getPosition();
}
