#include "menu.h"

Menu::Menu()
{
    ngl::NGLInit::instance();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // White Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // clear the screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

Menu::~Menu()
{
    std::cout<<"Shutting down SDL";
}

void Menu::resize(int _w, int _h)
{
    glViewport(0,0, _w  , _h );
    m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.1f, 200.0f );
    m_width=_w;
    m_height=_h;
}

void Menu::draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White Background
    glViewport( 0, 0, m_width, m_height );
    // clear the screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}

