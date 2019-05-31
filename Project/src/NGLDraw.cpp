#include "NGLDraw.h"

const static float INCREMENT=0.01f;
const static float ZOOM=0.05f;
constexpr auto PBR="PBR";

NGLDraw::NGLDraw()
{
    m_teapotHealth = 7;
    //Set initial game score
    m_score = 0;
    //Set spaceships intial angle
    teapot.setRotation(90);
    //Start timer
    timer.Start();

    m_rotate=false;

    // mouse rotation values set to 0
    m_spinXFace=0;
    m_spinYFace=0;

    ngl::NGLInit::instance();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Black Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // now to load the shader and set the values
    // grab an instance of shader manager
    ngl::ShaderLib* shader = ngl::ShaderLib::instance();
    // we are creating a shader called PBR to save typos
    // in the code create some constexpr
    constexpr auto vertexShader  = "PBRVertex";
    constexpr auto fragShader    = "PBRFragment";
    // create the shader program
    shader->createShaderProgram( PBR );
    // now we are going to create empty shaders for Frag and Vert
    shader->attachShader( vertexShader, ngl::ShaderType::VERTEX );
    shader->attachShader( fragShader, ngl::ShaderType::FRAGMENT );
    // attach the source
    shader->loadShaderSource( vertexShader, "shaders/PBRVertex.glsl" );
    shader->loadShaderSource( fragShader, "shaders/PBRFragment.glsl" );
    // compile the shaders
    shader->compileShader( vertexShader );
    shader->compileShader( fragShader );
    // add them to the program
    shader->attachShaderToProgram( PBR, vertexShader );
    shader->attachShaderToProgram( PBR, fragShader );
    // now we have associated that data we can link the shader
    shader->linkProgramObject( PBR );
    // and make it active ready to load values
    ( *shader )[ PBR ]->use();
    // We now create our view matrix for a static camera
    //Original Camera
    // ngl::Vec3 from( 0.0f, 2.0f, 2.0f );
    // ngl::Vec3 to( 0.0f, 0.0f, 0.0f );
    // ngl::Vec3 up( 0.0f, 1.0f, 0.0f );
    //trial view matrix
    //from = B/F & U/D
    ngl::Vec3 from( 0.0f, 10.0f, 10.0f );
    ngl::Vec3 to( 0.0f, 2.0f, 1.0f );
    ngl::Vec3 up( 0.0f, 1.0f, 0.0f );
    // now load to our new camera
    m_view=ngl::lookAt(from,to,up);
    shader->setUniform( "camPos", from );
    // setup the default shader material and light porerties
    // these are "uniform" so will retain their values
    shader->setUniform("lightPosition",0.0f,2.0f,2.0f);
    shader->setUniform("lightColor",400.0f,400.0f,400.0f);
    shader->setUniform("exposure",2.2f);
    shader->setUniform("albedo",0.950f, 0.71f, 0.29f);

    shader->setUniform("metallic",1.02f);
    shader->setUniform("roughness",0.38f);
    shader->setUniform("ao",0.2f);
    ngl::VAOPrimitives::instance()->createTrianglePlane("floor",20,20,1,1,ngl::Vec3::up());

    shader->use(ngl::nglCheckerShader);
    shader->setUniform("lightDiffuse",1.0f,1.0f,1.0f,1.0f);
    shader->setUniform("checkOn",true);
    shader->setUniform("lightPos",0.0f,2.0f,2.0f);
    shader->setUniform("colour1",0.9f,0.9f,0.9f,1.0f);
    shader->setUniform("colour2",0.9f,0.9f,0.9f,1.0f);
    shader->setUniform("checkSize",60.0f);

}

NGLDraw::~NGLDraw()
{
    std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLDraw::resize(int _w, int _h)
{
    glViewport(0,0, _w  , _h );
    m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.1f, 200.0f );
    m_width=_w;
    m_height=_h;
}

void NGLDraw::draw(float _delta)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Black Background

    //Spawn asteroids every 2 seconds
    if (timer.GetTime() > SPAWN_TIME)
    {
        timer.Reset();

        Asteroid asteroid;
        //Adds asteroid object to vector array
        asteroidVec.push_back(asteroid);
    }

    glViewport( 0, 0, m_width, m_height );
    // clear the screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // grab an instance of the shader manager
    ngl::ShaderLib* shader = ngl::ShaderLib::instance();
    ( *shader )[ "PBR" ]->use();

    // Rotation based on the mouse position for our global transform
    ngl::Mat4 rotX;
    ngl::Mat4 rotY;
    // create the rotation matrices
    rotX.rotateX( m_spinXFace );
    rotY.rotateY( m_spinYFace );
    // multiply the rotations
    m_mouseGlobalTX = rotX * rotY;
    // add the translations
    m_mouseGlobalTX.m_m[ 3 ][ 0 ] = m_modelPos.m_x;
    m_mouseGlobalTX.m_m[ 3 ][ 1 ] = m_modelPos.m_y;
    m_mouseGlobalTX.m_m[ 3 ][ 2 ] = m_modelPos.m_z;
    // get the VBO instance and draw the built in teapot
    ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
    shader->setUniform("colourIn", 1.0f, 0.0f, 0.0f);
    //****All objects are drawn here****//
    teapot.Draw(m_view, m_mouseGlobalTX, m_project, _delta);

    //shader->setUniform("colourIn", 0.5f, 0.0f, 0.0f);

    ngl::Mat4 tp;
    tp.translate(200, 0, 0);

    shader->use(ngl::nglCheckerShader);
    ngl::Mat4 tx;
    tx.translate(0.0f,-0.45f,0.0f);
    ngl::Mat4 MVP=m_project*m_view*m_mouseGlobalTX*tx;
    ngl::Mat3 normalMatrix=m_view*m_mouseGlobalTX;
    normalMatrix.inverse().transpose();
    shader->setUniform("MVP",MVP);
    shader->setUniform("normalMatrix",normalMatrix);
    prim->draw("floor");

    for (int i = 0; i < asteroidVec.size() ; i++)
    {
        asteroidVec[i].Draw(m_view, m_mouseGlobalTX, m_project, _delta);
    }

    //Collision detection between bullets(shot) and asteroid
    if (teapot.GetNumberOfBullets() > 0)
    {
        for (int i = 0; i < teapot.GetNumberOfBullets(); i++)
        {
            for (int j = 0; j < asteroidVec.size(); j++)
            {
                //collision between asteroid and bullet
                bool isCollided = sphereSphereCollision(asteroidVec[j].GetPosition(), asteroidVec[j].GetRadius(), teapot.GetBullets()[i].GetPosition(), teapot.GetBullets()[i].GetRadius());

                if (isCollided)
                {
                    teapot.RemoveBullet(i);

                    asteroidVec[j].Damage();

                    //Increase the score by the asteroid's specific score value
                    if (asteroidVec[j].GetHealth() <= 0)
                    {
                        //Remove asteroid
                        std::vector<Asteroid>::iterator it;

                        m_score += asteroidVec[j].GetScoreAmount();

                        std::cout << "Score: " << m_score << std::endl;

                        //Remove specific asteroid when health is 0.
                        it = asteroidVec.begin() + j;
                        asteroidVec.erase(it);
                    }

                    break;
                }
            }
        }
    }

    // Check if any asteroids have been created for collision check
    if (asteroidVec.size() > 0)
    {
        // Loop over all the asteroids and check if any of them have collided with the teaship
        for (int i = 0; i < asteroidVec.size(); i++)
        {
            //Collision between asteroid and spaceship
            bool isCollided = sphereSphereCollision(asteroidVec[i].GetPosition(), asteroidVec[i].GetRadius(), teapot.GetPosition(), 1);

            if (isCollided)
            {
                std::vector<Asteroid>::iterator it;
                //Remove specific asteroid when teapot collides, 'i' amount accross the vector array .
                it = asteroidVec.begin() + i;
                asteroidVec.erase(it);
                //Print health
                std::cout << "Teapot Health:" << teapotHealth() << std::endl;
                //Damage teapot
                teapotDamage();
                //Once teapot health reaches 0, game over
                if(teapotHealth() <= 0)
                {
                    std::cout << "YOU LOSE" << std::endl;
                }
            }
        }
    }

}



//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mouseMoveEvent (const SDL_MouseMotionEvent &_event)
{
    if(m_rotate && _event.state &SDL_BUTTON_LMASK)
    {
        int diffx=_event.x-m_origX;
        int diffy=_event.y-m_origY;
        m_spinXFace += (float) 0.5f * diffy;
        m_spinYFace += (float) 0.5f * diffx;
        m_origX = _event.x;
        m_origY = _event.y;
        //this->draw();
    }
    // right mouse translate code
    else if(m_translate && _event.state &SDL_BUTTON_RMASK)
    {
        int diffX = (int)(_event.x - m_origXPos);
        int diffY = (int)(_event.y - m_origYPos);
        m_origXPos=_event.x;
        m_origYPos=_event.y;
        m_modelPos.m_x += INCREMENT * diffX;
        m_modelPos.m_y -= INCREMENT * diffY;
        //this->draw();
    }
}


//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mousePressEvent (const SDL_MouseButtonEvent &_event)
{
    // this method is called when the mouse button is pressed in this case we
    // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
    if(_event.button == SDL_BUTTON_LEFT)
    {
        m_origX = _event.x;
        m_origY = _event.y;
        m_rotate =true;
    }
    // right mouse translate mode
    else if(_event.button == SDL_BUTTON_RIGHT)
    {
        m_origXPos = _event.x;
        m_origYPos = _event.y;
        m_translate=true;
    }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mouseReleaseEvent (const SDL_MouseButtonEvent &_event)
{
    // this event is called when the mouse button is released
    // we then set Rotate to false
    if (_event.button == SDL_BUTTON_LEFT)
    {
        m_rotate=false;
    }
    // right mouse translate mode
    if (_event.button == SDL_BUTTON_RIGHT)
    {
        m_translate=false;
    }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::wheelEvent(const SDL_MouseWheelEvent &_event)
{

    // check the diff of the wheel position (0 means no change)
    if(_event.y > 0)
    {
        m_modelPos.m_z+=ZOOM;
        //this->draw();
    }
    else if(_event.y <0 )
    {
        m_modelPos.m_z-=ZOOM;
        //this->draw();
    }

    // check the diff of the wheel position (0 means no change)
    if(_event.x > 0)
    {
        m_modelPos.m_x-=ZOOM;
        //this->draw();
    }
    else if(_event.x <0 )
    {
        m_modelPos.m_x+=ZOOM;
        //this->draw();
    }
}
//----------------------------------------------------------------------------------------------------------------------

/********************************************************* OWN CODE *********************************************************/

void NGLDraw::keyboardPressEvent(const SDL_Event &_event)
{
    teapot.keyboardPressEvent(_event);

    //Creates more asteroids (for testing)
    //if (_event.key.keysym.sym == SDLK_SPACE)
    //{
        //Asteroid asteroid;
        //Adds asteroid object to vector array
        //asteroidVec.push_back(asteroid);
    //}
}

//Collisions
bool NGLDraw::sphereSphereCollision(ngl::Vec3 _pos1, GLfloat _radius1, ngl::Vec3 _pos2, GLfloat _radius2 )
{
    //std::cout << _pos1.m_x << " : " << _pos1.m_y << " : " << _pos1.m_z << std::endl;
    //std::cout << _pos2.m_x << " : " << _pos2.m_y << " : " << _pos2.m_z << std::endl;
    // the relative position of the spheres
    ngl::Vec3 relPos;
    //min an max distances of the spheres
    GLfloat dist;
    GLfloat minDist;
    GLfloat len;
    relPos =_pos1-_pos2;
    // and the distance
    len=relPos.length();
    dist=len*len;
    minDist =_radius1+_radius2;
    // if it is a hit
    if(dist <=(minDist * minDist))
    {
        //std::cout << "Collided" << std::endl;
        //SpaceShip().score = 10;
        return true;
    }
    else
    {
        //std::cout << "NOT dskljjfoisjdoijfoisjdoif Collided" << std::endl;
        return false;
    }
}

int NGLDraw::GetScore()
{
    return m_score;
}

void NGLDraw::ResetScore()
{
    m_score = 0;
}

void NGLDraw::teapotDamage()
{
    m_teapotHealth--;
}

int NGLDraw::teapotHealth()
{
    return m_teapotHealth;
}
