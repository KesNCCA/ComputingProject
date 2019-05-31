#include "shot.h"

shot::shot(ngl::Transformation m_transform, float _angle)
{
    //sets both angle and position (not speed) the same as the teapot, so they fire from the correct origin and direction
    this->m_transform = m_transform;
    this->m_angle = _angle;

    m_radius = 0.2f;
}

shot::~shot(){}

void shot::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float delta)
{

    ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

    //low poly sphere (bullets)
    prim->createSphere("sphere", m_radius, 1);

    bool isSwitchingSides = false;

    //bullet moves in the direction that the ship is moving
    float x = (float) sin((float)(m_transform.getRotation().m_y + m_angle) * ngl::PI / 180.0f)*BULLET_SPEED;
    float y = (float) cos((float)(m_transform.getRotation().m_y + m_angle) * ngl::PI / 180.0f)*BULLET_SPEED;

    //bullet switches sides
    if (m_transform.getPosition().m_x >= 7 || m_transform.getPosition().m_x <= -7)
    {
        isSwitchingSides = true;
    }
    if (m_transform.getPosition().m_z >= 7 || m_transform.getPosition().m_z <= -7)
    {
        isSwitchingSides = true;
    }

    if (isSwitchingSides)
    {
        //remove from vector
        m_transform.setPosition(m_transform.getPosition().m_x * -1.0f, m_HeightPos, m_transform.getPosition().m_z * -1.0f);
        isSwitchingSides = false;
    }

    //prevAngle = m_transform.getRotation().m_y;
    m_transform.addPosition(x * (delta / 10.0f), 0.0, y * (delta / 10.0f));

    loadMatricesToShader(m_view, m_mouseGlobalTX, m_project);
    prim->draw( "sphere" );
}

float shot::GetRadius()
{
    return m_radius;
}

ngl::Vec3 shot::GetPosition()
{
    return m_transform.getPosition();
}
