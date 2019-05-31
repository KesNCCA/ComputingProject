#include "spaceship.h"

SpaceShip::SpaceShip()
{
    //set up initial values for valuables
    m_health = INITIAL_HEALTH;
    m_angle = 0.0f;
    m_initialAngle = 0.0f;
    m_offset = 0;
    m_acceleration = 0.0f;

    isMoving = false;
    //set initial spaceship position and rotation
    m_transform.setPosition(0.0, m_HeightPos, 0.0);
    m_transform.setRotation(0, 90, 0);

}

SpaceShip::~SpaceShip(){}

void SpaceShip::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project, float _delta)
{
    //loop over all the bullets created, add them to the vector array, and then draw them
    for (int i = 0; i < bullets.size() ; i++)
    {
        bullets[i].Draw(m_view, m_mouseGlobalTX, m_project, _delta);
    }

    ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

    bool isSwitchingSides = false;

    //Gets angle of teapot (getRotation) and multiplies it by sin or cos depending on the whether it's rotating left or right.
    float x = (float) sin((float)(m_transform.getRotation().m_y + m_initialAngle) * ngl::PI / 180.0f) * MOVEMENT_AMOUNT * m_acceleration + m_offset;
    float y = (float) cos((float)(m_transform.getRotation().m_y + m_initialAngle) * ngl::PI / 180.0f) * MOVEMENT_AMOUNT * m_acceleration + m_offset;

    //adds direction to teapot
    m_transform.addPosition(x, 0.0, y);

    //This code detects whether the position of the teapot exceeds that of the bounding square (plane)
    if (m_transform.getPosition().m_x >= 8 || m_transform.getPosition().m_x <= -8)
    {
        isSwitchingSides = true;
    }

    if (m_transform.getPosition().m_z >= 8 || m_transform.getPosition().m_z <= -8)
    {
        isSwitchingSides = true;
    }

    if (isSwitchingSides)
    {
        //multiplies the current position by -1 so that the teapot switches sides when it reaches the end of the plane
        m_transform.setPosition(m_transform.getPosition().m_x * -1.0f, m_HeightPos, m_transform.getPosition().m_z * -1.0f);
        isSwitchingSides = false;
    }

    //checks if player is turning, keeps ship moving in the direction previously moving in (while rotating)

     loadMatricesToShader(m_view, m_mouseGlobalTX, m_project);
     prim->draw( "teapot");

}

void SpaceShip::keyboardPressEvent(const SDL_Event &_event)
{
    //add to class later
    //Spaceship Movement
    m_angle = 0.0f;
    //add collision and deflection in 2 player with another ship

    //Get keyboard state for multiple simultaneous input
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    //shooting controls
    if ( _event.key.keysym.sym == SDLK_x )
    {
        //Reset model
        //make sure teapot faces correct direction
        m_transform.setPosition(0.0, m_HeightPos, 0.0);
        m_transform.setRotation(0, 90, 0);
        m_acceleration = 0.0f;
    }

    if ( _event.key.keysym.sym == SDLK_SPACE )
    {
        //std::cout << "SHOT" << std::endl;
        //std::cout << "Score: " << score;
        shot bullet(m_transform, m_initialAngle);
        //Adds bullet to vector array
        bullets.push_back(bullet);
    }

    if ( _event.key.keysym.sym == SDLK_UP )
    {
        //std::cout << "UP" << std::endl;
        //ACCELERATE
        m_acceleration += 0.1f;
    }
    if ( _event.key.keysym.sym == SDLK_DOWN )
    {
        //std::cout << "DOWN" << std::endl;
        m_acceleration -= 0.1f;

        if (m_acceleration <= 0)
        {
            m_acceleration = 0;
        }

    }
    if ( _event.key.keysym.sym == SDLK_LEFT)
    {
        //std::cout << "LEFT" << std::endl;

        m_angle += 10;
        m_transform.addRotation(0, m_angle, 0);
    }
    if ( _event.key.keysym.sym == SDLK_RIGHT)
    {  
        //std::cout << "RIGHT" << std::endl;

        m_angle -= 10;
        m_transform.addRotation(0, m_angle, 0);
    }
    //prints out angle of spaceship
    //std::cout << "Angle: " << m_transform.getRotation().m_y << std::endl;
}

void SpaceShip::setRotation(float _rotAngle)
{
    m_initialAngle = _rotAngle;
}

std::vector<shot> SpaceShip::GetBullets()
{
    return bullets;
}

int SpaceShip::GetNumberOfBullets()
{
    return bullets.size();
}

void SpaceShip::RemoveBullet(int _index)
{
    std::vector<shot>::iterator it;

    it = bullets.begin() + _index;
    bullets.erase(it);
}

ngl::Vec3 SpaceShip::GetPosition()
{
    return m_transform.getPosition();
}

int SpaceShip::GetHealth()
{
    return m_health;
}

void SpaceShip::Damage()
{
    m_health--;
}





