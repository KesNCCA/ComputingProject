#include "object.h"

Object::Object()
{
    HeightPos = 2.0f;
    xDirection = 0;
    yDirection = 0;
    zDirection = 0;
}

Object::~Object()
{

}

void Object::loadMatricesToShader(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project)
{
    ngl::ShaderLib* shader = ngl::ShaderLib::instance();
     shader->use("PBR");
     struct transform
     {
       ngl::Mat4 MVP;
       ngl::Mat4 normalMatrix;
       ngl::Mat4 M;
     };

     ngl::Transformation m;

      transform t;
      //to move objects
      t.M=m_view*m_mouseGlobalTX*m_transform.getMatrix();

      t.MVP=m_project*t.M;
      t.normalMatrix=t.M;
      t.normalMatrix.inverse().transpose();
      shader->setUniformBuffer("TransformUBO",sizeof(transform),&t.MVP.m_00);
}

void Object::Draw(ngl::Mat4 m_view, ngl::Mat4 m_mouseGlobalTX, ngl::Mat4 m_project)
{

}

void Object::keyboardPressEvent(const SDL_Event &_event)
{

}




