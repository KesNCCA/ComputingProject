#include "spaceship.h"
#include "shot.h"

#define MOVEMENT_AMOUNT 0.2f
#define MOVEMENT_OFFSET 8.0f

SpaceShip::SpaceShip()
{
    //set up initial values for valuables
    score = 0;
    angle = 0.0f;
    initialAngle = 0.0f;
    animationCounter = 0.0f;
    offset = 0;
    acceleration = 0.0f;
    prevAngle = 0.0f;
    isMoving = false;
    keepMoving = false;
    //set initial spaceship position and rotation
    m_transform.setPosition(0.0, HeightPos, 0.0);
    m_transform.setRotation(0, 90, 0);

}

SpaceShip::~SpaceShip(){}

void SpaceShip::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project)
{
    //loop over all the bullets created, add them to the vector array, and then draw them
    for (int i = 0; i < bullets.size() ; i++)
    {
        bullets[i].Draw(m_view, m_mouseGlobalTX, m_project);
    }



    ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

    float multiplier = 0.0f;

    // Update position based on movement speed (velocity vector)
        //x += vX;
        //y += vY;

    // Use Stokes' law to apply drag to the ship
        //vX = vX - vX * dragFactor;
        //vY = vY - vY * dragFactor;

    /*if (isMoving)
    {
        //Keeps spaceship moving after key has stopped being pressed
        if (animationCounter < MOVEMENT_OFFSET)
        {
            multiplier = animationCounter / MOVEMENT_OFFSET;
            animationCounter += 0.1f;
        }

        else
        {
            animationCounter = 0.0f;
            offset = 0.0f;

            isMoving = false;
        }
    }*/

    bool isSwitchingSides = false;

    float x = (float) sin((float)(m_transform.getRotation().m_y + initialAngle) * ngl::PI / 180.0f) * MOVEMENT_AMOUNT * acceleration + offset;
    float y = (float) cos((float)(m_transform.getRotation().m_y + initialAngle) * ngl::PI / 180.0f) * MOVEMENT_AMOUNT * acceleration + offset;
    prevAngle = m_transform.getRotation().m_y;
    m_transform.addPosition(x, 0.0, y);

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
        m_transform.setPosition(m_transform.getPosition().m_x * -1.0f, HeightPos, m_transform.getPosition().m_z * -1.0f);
        isSwitchingSides = false;
    }

    //checks if player is turning, keeps ship moving in the direction previously moving in (while rotating)
    if (keepMoving)
    {
        x = 0;
        y = 0;

        m_transform.addPosition(x, 0.0, y);
    }

     loadMatricesToShader(m_view, m_mouseGlobalTX, m_project);
     prim->draw( "teapot");

}

void SpaceShip::keyboardPressEvent(const SDL_Event &_event)
{
    //add to class later
    //Spaceship Movement
    angle = 0.0f;
    //add collision and deflection in 2 player with another ship

    //Get keyboard state for multiple simultaneous input
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    //shooting controls
    if (_event.key.keysym.sym == SDLK_x)
    {
        std::cout << "SHOT" << std::endl;
        //std::cout << "Score: " << score;
        shot bullet(m_transform, initialAngle);
        //Adds bullet to vector array
        bullets.push_back(bullet);
    }

    if (_event.key.keysym.sym == SDLK_SPACE)
    {
        std::cout << "Space" << std::endl;
        //Reset model
        //make sure teapot faces correct direction
        m_transform.setPosition(0.0, HeightPos, 0.0);
        m_transform.setRotation(0, 90, 0);
        acceleration = 0.0f;
    }
    if ( keyboard_state_array[SDL_SCANCODE_UP] && _event.key.keysym.sym == SDLK_UP )
    {
        std::cout << "UP" << std::endl;
        keepMoving = false;
        //ACCELERATE
        acceleration += 0.1f;
    }
    if (keyboard_state_array[SDL_SCANCODE_DOWN] && _event.key.keysym.sym == SDLK_DOWN)
    {
        std::cout << "DOWN" << std::endl;
        keepMoving = false;

        acceleration -= 0.1f;

        if (acceleration <= 0)
        {
            acceleration = 0;
        }

    }
    if ( keyboard_state_array[SDL_SCANCODE_LEFT] && _event.key.keysym.sym == SDLK_LEFT)
    {
        std::cout << "LEFT" << std::endl;
        keepMoving = true;


        angle += 10;
        m_transform.addRotation(0, angle, 0);
    }
    if (keyboard_state_array[SDL_SCANCODE_RIGHT] && _event.key.keysym.sym == SDLK_RIGHT)
    {  
        std::cout << "RIGHT" << std::endl;
        keepMoving = true;

        angle -= 10;
        m_transform.addRotation(0, angle, 0);
    }
    //prints out angle of spaceship
    std::cout << "Angle: " << m_transform.getRotation().m_y << std::endl;
}

void SpaceShip::Accelerate()
{
    // Create a normalized vector in the direction of travel
    //float xN = static_cast<float>(sin(2 * M_PI * (angle / 360)));
    //float yN = static_cast<float>(cos(2 * M_PI * (angle / 360)));

    // Add to velocity vector (using minus for y because Direct2D uses 0,0 as the top-left corner instead of bottom-left)
    //vX += xN * accFactor;
    //vY += yN * accFactor;
}

void SpaceShip::setRotation(float rotAngle)
{
    initialAngle = rotAngle;
}

std::vector<shot> SpaceShip::GetBullets()
{
    return bullets;
}

int SpaceShip::GetNumberOfBullets()
{
    return bullets.size();
}

void SpaceShip::RemoveBullet(int index)
{
    std::vector<shot>::iterator it;

    it = bullets.begin() + index;
    bullets.erase(it);
}

ngl::Vec3 SpaceShip::GetPosition()
{
    return m_transform.getPosition();
}





