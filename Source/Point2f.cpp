
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Point2f.hpp"




// Accessors

GLfloat Point2f::getX() const
{
	return _x;
}

GLfloat Point2f::getY() const
{
	return _y;
}


// Mutators

void Point2f::setX(GLfloat x)
{
	_x = x;
}

void Point2f::setY(GLfloat y)
{
	_y = y;
}

void Point2f::setXY(GLfloat x, GLfloat y)
{
	_x = x;
	_y = y;
}

//Constructor

Point2f::Point2f()
{
	_x = 0;
	_y = 0;

}

Point2f::Point2f(GLfloat x, GLfloat y)
{
	_x = x;
	_y = y;

}

//return reference to the lvalue
Point2f& Point2f::operator =(const Point2f &a)
{		_x = a.getX();
		_y = a.getY();
		return *this;
}	

//Check for equality/not equality from other value of Class

bool Point2f::operator ==(const Point2f &a) const
{
	return _x == a.getX() && _y == a.getY();
}

bool Point2f::operator !=(const Point2f &a) const
{
	return _x != a.getX() || _y != a.getY();
}

//Set the vector to zero
void Point2f::zero()
{
	_x = _y = 0;
}

Point2f &Point2f::operator +=(const Point2f &a)
{
		_x += a.getX();
		_y += a.getY();
		return *this;
}

Point2f &Point2f::operator -=(const Point2f &a)
{
		_x -= a.getX();
		_y -= a.getY();
		return *this;
}

Point2f &Point2f::operator *=(GLfloat a)
{
	_x *=a;
	_y *=a;
	return *this;
}


Point2f &Point2f::operator /=(GLfloat a)
{
	_x /=a;
	_y /=a;
	return *this;
}

//Print value
void Point2f::addScaledVector(const Point2f& vector, GLfloat scale)
{
	_x += vector._x * scale;
	_y += vector._y * scale;
}


void Point2f::getPoint2fprint()
{
	std::cout << "x: " << _x << " y: " << _y  << std::endl;
}

GLfloat Point2f::magnitude() const
{
	return sqrt(_x*_x + _y * _y);
}

GLfloat Point2f::squareMagnitude() const
{
	return (_x * _x + _y * _y);
}

void Point2f::normalize()
{
	GLfloat l = magnitude();
	
	if(l > 0)
	{
		(*this) *= ((GLfloat) 1) / l;
	}
}

void Point2f::reset()
{
	_x = 0;
	_y = 0;
}


GLfloat dotProduct(const Point2f &v1, const Point2f &v2)
{
	return v1._x * v2._x + v1._y * v2._y;
}
