#pragma once

#include <iostream>
#include "Point2f.hpp"
#include "Ball.hpp"
enum PegType
{
	circle,
	rectangle,
	triangle,
	pentagon,
	hexagon
};

class Peg
{
	public:
	Point2f position;
	Point2f velocity;
	Point2f * vertices;
	PegType type;
	float redColor;
	float blueColor;
	float greenColor;
	GLfloat radius;
    GLfloat mass;
    GLfloat rotation; //radians mode
   // GLfloat elasticity;
    GLUquadric *quadric;  /* For rendering. */
    int slices;
    int subs;
    int loops;    /* For rendering. */
    int hp;
    Peg();
    void initPlacement(GLfloat x, GLfloat y, PegType t, GLfloat size, GLfloat r);
	void RenderPeg(float sx, float sy, float sz);	
	void FlashColor();
	void FadeColor(GLfloat time);
	bool circlePegCollision(Ball &ball, GLfloat time); 
	bool polyPegCollision(Ball &ball, bool visualDebug);
	bool polyPegCollision_p(Ball &ball);
};
