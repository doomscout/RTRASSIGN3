#include "Arena.hpp"

Arena::Arena()
{
  GLfloat halfLength = 99.5;  
  min.setXY(-halfLength, -halfLength);
  max.setXY(halfLength, halfLength);
  momentum.setXY(0.0, 0.0);
  
}


void Arena::displayArena()
{
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(min.getX(), min.getY(), 0.0);
  glVertex3f(max.getX(), min.getY(), 0.0);
  glVertex3f(max.getX(), max.getY(), 0.0);
  glVertex3f(min.getX(), max.getY(), 0.0);
  glEnd();
}
