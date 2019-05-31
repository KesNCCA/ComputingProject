#include "asteroid.h"

Asteroid::Asteroid()
{
    //set initial asteroid position
    m_transform.setPosition(4.0, m_HeightPos, 4.0);

    m_Xdir = RandomMovement() * 0.01f;
    m_Ydir = RandomMovement() * 0.01f;

    m_radius = _RADIUS_;

    m_health = INITIAL_HEALTH;
    m_scoreAmount = INITIAL_SCORE;
}

Asteroid::~Asteroid(){}

void Asteroid::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float delta)
{
     ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

     bool isSwitchingSides = false;
    //This code detects whether the position of the asteroid exceeds that of the bounding square (plane)
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
         //multiplies the current position by -1 so that the asteroid switches sides when it reaches the end of the plane
         m_transform.setPosition(m_transform.getPosition().m_x * -1.0f, m_HeightPos, m_transform.getPosition().m_z * -1.0f);
         isSwitchingSides = false;
     }

     //high poly sphere (asteroids)
     prim->createSphere("sphere", m_radius, 200);
     //prevAngle = m_transform.getRotation().m_y;
     m_transform.addPosition(m_Xdir * (delta / 20.0f), 0.0, m_Ydir * (delta / 20.0f));


     loadMatricesToShader(m_view, m_mouseGlobalTX, m_project);
     prim->draw( "sphere" );
}

int Asteroid::RandomMovement()
{

     int random_number = (rand()%10)+1; // rand() return a number between ​0​ and RAND_MAX
     //std::cout << "random number for asteroid movement: "<< random_number;

     return random_number;
}

float Asteroid::GetRadius()
{
    return m_radius;
}

ngl::Vec3 Asteroid::GetPosition()
{
    return m_transform.getPosition();
}

void Asteroid::Damage()
{
    m_health--;
}

int Asteroid::GetHealth()
{
    return m_health;
}

int Asteroid::GetScoreAmount()
{
    return m_scoreAmount;
}
