#include "asteroid.h"

#define MOVEMENT_AMOUNT 0.5f
#define _RADIUS_ 0.5f

Asteroid::Asteroid()
{
    //set initial asteroid position
    m_transform.setPosition(4.0, HeightPos, 4.0);

    x = RandomMovement() * 0.01f;
    y = RandomMovement() * 0.01f;

    radius = _RADIUS_;

    health = INITIAL_HEALTH;
    scoreAmount = INITIAL_SCORE;
}

Asteroid::~Asteroid(){}

void Asteroid::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project)
{
     ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

     bool isSwitchingSides = false;



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

     //high poly sphere (asteroids)
     prim->createSphere("sphere",radius,200);
     //prevAngle = m_transform.getRotation().m_y;
     m_transform.addPosition(x, 0.0, y);


     loadMatricesToShader(m_view, m_mouseGlobalTX, m_project);
     prim->draw( "sphere" );
}

int Asteroid::RandomMovement()
{

     int random_number = (rand()%10)+1; // rand() return a number between ​0​ and RAND_MAX
     //std::cout << "random number for asteroid movement: "<< random_number;
     std::cout<< random_number << std::endl;
     return random_number;
}

void Asteroid::keyboardPressEvent(const SDL_Event &_event)
{
    //Spaceship Movement
    float angle = 0.0f;

    if (_event.key.keysym.sym == SDLK_SPACE)
    {      
        std::cout << "Space" << std::endl;
    }
    if (_event.key.keysym.sym == SDLK_w)
    {
        std::cout << "UP" << std::endl;
        // check if the asteroid is moving down, if so reset it for moving up
        if (zDirection > 0)
        {
            zDirection = 0;
            zDirection -= MOVEMENT_AMOUNT;
        }
        else
        {
            zDirection -= MOVEMENT_AMOUNT;
        }

        m_transform.addPosition(0.0, 0.0, zDirection);
    }
    if (_event.key.keysym.sym == SDLK_s)
    {
        std::cout << "DOWN" << std::endl;

        if (zDirection < 0)
        {
            zDirection = 0;
            zDirection += MOVEMENT_AMOUNT;
        }
        else
        {
            zDirection += MOVEMENT_AMOUNT;
        }


        m_transform.addPosition(0.0, 0.0, zDirection);
    }
    if (_event.key.keysym.sym == SDLK_a)
    {
        std::cout << "LEFT" << std::endl;

        if (xDirection > 0)
        {
            xDirection = 0;
            xDirection -= MOVEMENT_AMOUNT;
        }
        else
        {
            xDirection -= MOVEMENT_AMOUNT;
        }

        angle += 10;
        m_transform.addPosition(xDirection, 0.0, 0.0);
        m_transform.addRotation(0, angle, 0);
    }
    if (_event.key.keysym.sym == SDLK_d)
    {
        std::cout << "RIGHT" << std::endl;

        if (xDirection < 0)
        {
            xDirection = 0;
            xDirection += MOVEMENT_AMOUNT;
        }
        else
        {
            xDirection += MOVEMENT_AMOUNT;
        }

        angle -= 10;
        m_transform.addPosition(xDirection, 0.0, 0.0);
        m_transform.addRotation(0, angle, 0);
    }
}

float Asteroid::GetRadius()
{
    return radius;
}

ngl::Vec3 Asteroid::GetPosition()
{
    return m_transform.getPosition();
}

void Asteroid::Damage()
{
    health--;
}

int Asteroid::GetHealth()
{
    return health;
}


int Asteroid::GetScoreAmount()
{
    return scoreAmount;
}
