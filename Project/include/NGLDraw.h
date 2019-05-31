#ifndef NGLDRAW_H_
#define NGLDRAW_H_

#include <SDL.h>
#include <ngl/Transformation.h>
#include <ngl/Mat4.h>
#include <ngl/Vec3.h>
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>
#include <ngl/Transformation.h>
#include <ngl/AbstractVAO.h>
//own classes
#include "timer.h"
#include "spaceship.h"
#include "asteroid.h"
#include "shot.h"
//#include "statemanager.h

#define MOVEMENT_AMOUNT 0.5f

// Time for each asteroid to spawn in game
#define SPAWN_TIME 2

class NGLDraw
{
  public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
    //----------------------------------------------------------------------------------------------------------------------
    NGLDraw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor used to remove any NGL stuff created
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLDraw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize our screen and set the camera aspect ratio
    /// @param[in] _w the new width
    /// @param[in] _h the new height
    //----------------------------------------------------------------------------------------------------------------------
    void resize(int _w, int _h);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void draw(float delta);
    //own code
    void buildVAO();

    void keyboardPressEvent(const SDL_Event &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (const SDL_MouseMotionEvent &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse button is presses
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent (const SDL_MouseButtonEvent &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent (const SDL_MouseButtonEvent &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent(const SDL_MouseWheelEvent &_event);

    int GetScore();

    void ResetScore();

    void changeState();

    //health of teapot
    int teapotHealth();

    //teapot damage function
    void teapotDamage();

  private :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform data to the shaders
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToShader();
    void loadMatricesToShaderAsteroid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Creates bounding box for collision detection
    //----------------------------------------------------------------------------------------------------------------------
    //void BBoxCollision();
    bool sphereSphereCollision(ngl::Vec3 _pos1, GLfloat _radius1, ngl::Vec3 _pos2, GLfloat _radius2 );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the x rotation mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_spinXFace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the y rotation mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_spinYFace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the mouse button is pressed when dragging
    //----------------------------------------------------------------------------------------------------------------------
    bool m_rotate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the Right mouse button is pressed when dragging
    //----------------------------------------------------------------------------------------------------------------------
    bool m_translate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous x mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_origX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous y mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_origY;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous x mouse value for Position changes
    //----------------------------------------------------------------------------------------------------------------------
    int m_origXPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous y mouse value for Position changes
    //----------------------------------------------------------------------------------------------------------------------
    int m_origYPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the global mouse transforms
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_mouseGlobalTX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Our Camera
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_view;
    ngl::Mat4 m_project;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    int m_width;
    int m_height;


    float xDirection;
    float zDirection;

    SpaceShip teapot;

    Timer timer;

    std::vector<Asteroid> asteroidVec;

    //asteroid health
    int health;

    //teapot health
    int m_teapotHealth;

    //game score
    int m_score;
};


#endif
