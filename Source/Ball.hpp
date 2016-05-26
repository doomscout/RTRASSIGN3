#pragma once

#include <iostream>
#include "Point2f.hpp"

class Ball
{
public:
	Point2f position;
	Point2f velocity;
	//variables for predicted_Trajectory
	Point2f position_p;
	Point2f velocity_p;
	
	Point2f acceleration;
	Point2f force;
	float redColor;
	float blueColor;
	float greenColor;
	//GLfloat rotationShoot;
	GLfloat radius;
    GLfloat mass;
    GLfloat damp;
    GLfloat elasticity; 
    GLUquadric *quadric;  /* For rendering. */
    int slices;
    int loops;    /* For rendering. */
    bool isOnFire;
	Ball();
	
	//Copy constructor
	Ball(const Ball &obj);
	~Ball();
	//Ball(Point2f pos, Point2f velocity);
	void initPlacement(GLfloat x, GLfloat y);
	void displayParticle(float sx, float sy, float sz);	
	void FlashColor();
	void FadeColor(GLfloat time);
	void ClearForce();
	void printVelocity();
};
