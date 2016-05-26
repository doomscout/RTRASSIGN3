#include "Ball.hpp"

Ball::Ball()
{
	GLUquadric *q = gluNewQuadric();
	position.setXY(0,0);
	velocity.setXY(0,0);
	acceleration.setXY(0,-9.8); //gravity
	redColor = 1;
	blueColor = 1;
	greenColor = 1;
    radius =4.0;
    mass = 10.0;
    damp = 0.98;
    elasticity = 0.99998;
	quadric = q;
    slices = 10;
    loops = 3; 
    
}


#if 1
Ball::Ball(const Ball &obj)
{
	quadric = obj.quadric;
	position = obj.position;
	acceleration = obj.acceleration;
	radius = obj.radius;
	damp = obj.damp;
	redColor = obj.redColor;
	blueColor = obj.blueColor;
	greenColor = obj.greenColor;
    mass = obj.mass;
    
    elasticity = obj.elasticity;
    slices = obj.slices;
    loops = obj.loops; 
    
    //return *this;
}
#endif
Ball::~Ball()
{
}
void Ball::initPlacement(GLfloat x, GLfloat y)
{

	position.setXY(x,y);
	velocity.setXY(0,0);
    isOnFire = false;
	
}

void Ball::displayParticle(float sx, float sy, float sz)
{
  glPushMatrix();
  glScalef(sx, sy, sz);
  glColor3f(redColor, blueColor, greenColor);
  gluDisk(quadric, 0.0, radius, slices, loops);
  glPopMatrix();
}


void Ball::FlashColor()
{
//	std::cout << "Red" << std::endl;
	blueColor = 0;
	greenColor = 0;
}

void Ball::FadeColor(GLfloat time)
{
	time = time * 0.001 * 0.5;
	if(greenColor <= 1.0)
	{
		//std::cout << "Time: " << time << std::endl;
		greenColor += time;
		blueColor += time;
		
		if(greenColor >= 1.0)
		{
			greenColor = 1.0;
			blueColor = 1.0;
		}	
	}	
}

void Ball::printVelocity()
{
	std::cout << "Velocity x : " << velocity._x << "  Velocity y :" <<velocity._y << std::endl;
	std::cout << "Velocity_p x : " << velocity_p._x << "  Velocity_p y :" <<velocity_p._y << std::endl;
	std::cout << "Position x : " << position._x << "  Position y :" <<position._y << std::endl;
	std::cout << "Position_x : " << position_p._x << "  Position_y :" <<position_p._y << std::endl;	
}

