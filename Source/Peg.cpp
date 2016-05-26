#include "Peg.hpp"
Peg::Peg()
{
	GLUquadric *q = gluNewQuadric();
	position.setXY(0,0);
	//velocity.setXY(0,0);
    radius =1.0;
    mass = 1.0;
    
    redColor = 1;
	blueColor = 1;
	greenColor = 1;
//    elasticity = 1.0;
	quadric = q;
    slices = 10;
    loops = 3; 
    hp = 2;
}
void Peg::initPlacement(GLfloat x, GLfloat y, PegType t, GLfloat size, GLfloat r)
{
	type = t;
	position.setXY(x,y);
	radius = size;
	//velocity.setXY(0, 0);
	rotation = r;
	if(t == circle)
	{
		vertices = new Point2f[1];
		vertices[0].setXY(0,0);
	}
	if(t == rectangle)
	{
		
		vertices = new Point2f[4];
		vertices[0].setXY(2 * size, -1 * size);
		vertices[1].setXY(-2 * size, -1 * size);
		vertices[2].setXY(2 * size,1 * size);
		vertices[3].setXY(-2 * size,1 * size);
	}
	
	if(t == triangle)
	{
		subs = 3;
		vertices = new Point2f[4];
		for (int i = 0; i <= 3; ++i)
			vertices[i].setXY( radius * cosf(2.0f * i * PI_F / subs) , 
			radius * sinf(2.0f * i * PI_F / subs));
	}
	
	if(t == pentagon)
	{
		subs = 5;
		vertices = new Point2f[6];
		for (int i = 0; i <= 5; ++i)
			vertices[i].setXY( radius * cosf(2.0f * i * PI_F / subs) , 
			radius * sinf(2.0f * i * PI_F / subs));
	}
	
	if(t == hexagon)
	{
		subs = 6;
		vertices = new Point2f[7];
		for (int i = 0; i <= 6; ++i)
			vertices[i].setXY( radius * cosf(2.0f * i * PI_F / subs) , 
			radius * sinf(2.0f * i * PI_F / subs));
	}
	
}

void Peg::RenderPeg(float sx, float sy, float sz)
{
	if(type == circle)
	{
		glPushMatrix();
		glColor3f(redColor, blueColor, greenColor);
		glTranslatef(position.getX(), position.getY(), 0.0);
		//glRotatef(180.0f * peg[i].rotation / PI_F, 0.0f, 0.0f, 1.0f); 	  
		//glScalef(sx, sy, sz);
		gluDisk(quadric, 0.0, radius, slices, loops);
		glPopMatrix();
	}
	
	if(type == rectangle)
	{
		glPushMatrix();
		glColor3f(redColor, blueColor, greenColor);
	  	glTranslatef(position.getX(), position.getY(), 0.0);
		glRotatef(180.0f * rotation / PI_F, 0.0f, 0.0f, 1.0f);
		glScalef(sx * radius, sy * radius, sz* radius);
		glBegin(GL_TRIANGLE_STRIP);
		for(int i = 0; i < 4; i++)
			glVertex2f(vertices[i]._x, vertices[i]._y);
		glEnd();
		glPopMatrix();
	}
	
	if(type == triangle)
	{
		glPushMatrix();
		glColor3f(redColor, blueColor, greenColor);	
	  	glTranslatef(position.getX(), position.getY(), 0.0);
		glRotatef(180.0f * rotation / PI_F, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLE_FAN);
		glScalef(sx, sy, sz);
		glVertex2f(0.0f, 0.0f);
		for (int i = 0; i <= 3; ++i)
			glVertex2f(radius * cosf(2.0f * i * PI_F / 3),
					   radius * sinf(2.0f * i * PI_F / 3));
		glEnd();
		glPopMatrix();
	}
	
	if(type == pentagon)
	{
	    glPushMatrix();
	  	glTranslatef(position.getX(), position.getY(), 0.0);
		glRotatef(180.0f * rotation / PI_F, 0.0f, 0.0f, 1.0f);
		glColor3f(redColor, blueColor, greenColor);
		glBegin(GL_TRIANGLE_FAN);
		glScalef(sx, sy, sz);
		glVertex2f(0.0f, 0.0f);
		for (int i = 0; i <= 5; ++i)
			glVertex2f(radius * cosf(2.0f * i * PI_F / 5),
					   radius * sinf(2.0f * i * PI_F / 5));
		glEnd();
		glPopMatrix();
	}
	
    if(type == hexagon)
	{
		glPushMatrix();
	  	glTranslatef(position.getX(), position.getY(), 0.0);
		glRotatef(180.0f * rotation / PI_F, 0.0f, 0.0f, 1.0f);
		glColor3f(redColor, blueColor, greenColor);
		glBegin(GL_TRIANGLE_FAN);
		glScalef(sx, sy, sz);
		glVertex2f(0.0f, 0.0f);
		for (int i = 0; i <= 6; ++i)
			glVertex2f(radius * cosf(2.0f * i * PI_F / 6),
					   radius * sinf(2.0f * i * PI_F / 6));
		glEnd();
		glPopMatrix();
	}
}



void Peg::FlashColor()
{
//	std::cout << "Red" << std::endl;
	blueColor = 0;
	greenColor = 0;
}

void Peg::FadeColor(GLfloat time)
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

//Cirlce To Edge Collision Function
bool Peg::circlePegCollision(Ball &ball, GLfloat time)
{
	GLfloat sum_radii, sum_radii_sq, n_mag_sq;
	Point2f normal;
	
	normal = ball.position - position;
	//GLfloat distance = normal.magitude();
	
	sum_radii = ball.radius + radius;
	sum_radii_sq = sum_radii * sum_radii;
	
	//std::cout << "x " << normal._x << std::endl;
	n_mag_sq = normal.squareMagnitude();
//	std::cout << " n_maq_sq:" << sum_radii_sq  << std::endl;
//	std::cout << "sum_radii_sq:" << sum_radii_sq << std::endl;
	if (n_mag_sq <= sum_radii_sq) 
	{
		std::cout << "x " << normal._x << std::endl;
		normal.normalize();
		std::cout << "normal x " << normal._x << std::endl;
		GLfloat velocityDotN = dotProduct(normal, ball.velocity);
		if(velocityDotN < 0)
		{
			ball.velocity._x -= 2.0f * velocityDotN * normal._x;
			ball.velocity._y -= 2.0f * velocityDotN * normal._y;
			
			ball.position._x += 2.0f * (sum_radii - radius + ball.radius) * normal._x * time;
			ball.position._y += 2.0f * (sum_radii - radius + ball.radius) * normal._y * time;
			
		}
		
		return true;
	}
	else 
	{
		return false;	
	}
}

//Circle to Edge Collision Function aka Poly Collision
bool Peg::polyPegCollision(Ball &ball, bool visualDebug)
{
	GLfloat collisionDist = INFINITY;
	bool isClosestEdge; 
	
	//Variables for edge collision
	Point2f vecFromVert;
	Point2f tangent, normal;
	GLfloat tangentComponent, normalComponent, edgeLenght;
	
	//Variables for Corner collision 
	
	int cornerIndex = -1, prevCornerIndex, nextCornerIndex;
	Point2f cornerNormal_1, cornerNormal_2;
	GLfloat cornerDist;
	
	//Variable for Rebound
	Point2f rebound;
	GLfloat orthogBallVelMag;
	GLfloat transPolyVelDotReb;
	
	//Calculate transformed co-ordinates from ball position
	Point2f orig(ball.position._x - position._x, ball.position._y - position._y);
	Point2f trans(cosf(rotation) * orig._x + sinf(rotation) * orig._y, 
	- sinf(rotation) * orig._x + cosf(rotation) * orig._y);
	
	//Calculate transformed co-ordinates from ball velocity
	
	Point2f transVel(cosf(rotation) * ball.velocity._x + sinf(rotation) * ball.velocity._y, 
	- sinf(rotation) * ball.velocity._x + cosf(rotation) * ball.velocity._y);
	
	//Calculate transformed co-ordinates from peg velocity...errr oh wait...it is zero!!
	Point2f zeroVeloc(0,0);
	Point2f transPegPolyVel(cosf(rotation) * zeroVeloc._x + sinf(rotation) * zeroVeloc._y, 
	- sinf(rotation) * zeroVeloc._x + cosf(rotation) * zeroVeloc._y);
	
	if(type == circle)
	{
		rebound = trans;
		collisionDist = rebound.magnitude()- (ball.radius * 2) - vertices[0].magnitude();
		rebound.normalize();
	}
	else
	{
		//check Edge collision
		for(int i = 0; i < subs; i++)
		{
			isClosestEdge = false;
			//Calculate vectFromVert 
			vecFromVert = trans - vertices[i];
			
			//Calculate tangent between two vertices
			tangent = vertices[i+1] - vertices[i];
			edgeLenght = tangent.magnitude();
			
			tangent.normalize();
			
			//calculate normal vector
			normal._x = tangent._y;
			normal._y = -tangent._x;
			
			//caluclate components
			tangentComponent = dotProduct(tangent, vecFromVert);
			normalComponent = dotProduct(normal, vecFromVert);
			
			if(normalComponent >= 0.0 && tangentComponent >= 0 && tangentComponent <= edgeLenght)
			{
				isClosestEdge = true;
				collisionDist = normalComponent - ball.radius;
				rebound._x = normal._x;
				rebound._y = normal._y;
				
			}
			
			//Visual Debug
			if(visualDebug)
			{
				//highlight edge with teal color if closest Edge is choiced
				glPushMatrix();
				if(isClosestEdge)
					glColor3f(0,1,1);
				else
					glColor3f(1,1,1);
				
				
				glTranslatef(position.getX(), position.getY(), 0.0);
				glRotatef(180.0f * rotation / PI_F, 0.0f, 0.0f, 1.0f);	
				
				Point2f vertices1 = vertices[i];// + position;
				Point2f vertices2 = vertices[i+1];// + position;
				glBegin(GL_LINES);
				glVertex2f(
				vertices1._x,
				vertices1._y
				);
				glVertex2f(
				vertices2._x, 
				vertices2._y);
				glEnd();
				glPopMatrix();
					
			}
		}
	}
	//if Edge don't collision and check corner collision
	
	if(collisionDist == INFINITY)
	{
		for(int i = 0; i < subs; i++)
		{
			Point2f cornerToBall;
			cornerToBall = trans - vertices[i];
			cornerDist = cornerToBall.magnitude() - ball.radius;
			
			if(cornerDist < collisionDist)
			{
				cornerIndex = i;
				nextCornerIndex = i + 1;
				if(i == 0)
					prevCornerIndex = subs - 1;
				else
					prevCornerIndex = i - 1;
				
				collisionDist = cornerDist;
				
				cornerToBall.normalize();
				rebound._x = cornerToBall._x;
				rebound._y = cornerToBall._y;
				
				//calculate cornerNomral_1 and cornerNomral_2
				if(dotProduct(rebound, transVel) > 0.0)
				{
					//check a segment line from current corner and previous corner
					cornerNormal_1 = vertices[cornerIndex] - vertices[prevCornerIndex];
					cornerNormal_1.normalize();
					
					//check a segment line from current corner and next corner
					cornerNormal_2 = vertices[cornerIndex] - vertices[nextCornerIndex];	
					cornerNormal_2.normalize();
					
					if(dotProduct(cornerNormal_1, transVel) < 0.0)
					{
						rebound = cornerNormal_1;
					}
					else if(dotProduct(cornerNormal_2, transVel) < 0.0)
					{
						rebound = cornerNormal_2;
					}
					else
					{
						rebound.reset();
						collisionDist = INFINITY;
					}				
				}
			}
		}
		//normalize rebound 
		rebound.normalize();
		
		//visual Debug Mode
		if(visualDebug)
		{
			glPushMatrix();
			glTranslatef(position.getX(), position.getY(), 0.0);
			glRotatef(180.0f * rotation / PI_F, 0.0f, 0.0f, 1.0f);	
			glColor3f(1,0,0);
			glPointSize(3);
			glBegin(GL_POINTS);
			glVertex2f(
			vertices[cornerIndex]._x, 
			vertices[cornerIndex]._y);
			glEnd();
			glPopMatrix();		
		}
	}
	
	
	
	if(collisionDist > 0.0f)
	{
		return false;
	}
	else
	{
		//calcuate component that gets mirrored
		orthogBallVelMag= dotProduct(rebound, transVel);
		transVel._x -= 2.0f * orthogBallVelMag * rebound._x;
		transVel._y -= 2.0f * orthogBallVelMag * rebound._y;
		
		//calculate transVelocity
		transPolyVelDotReb = dotProduct(rebound, transPegPolyVel);
		transVel._x += transPolyVelDotReb * rebound._x;
		transVel._y += transPolyVelDotReb * rebound._y;
		
		//setting ball's velocity with new velocity
		ball.velocity._x = cosf(rotation) * transVel._x - sinf(rotation) * transVel._y;
		ball.velocity._y = sin(rotation) * transVel._x + cosf(rotation) * transVel._y;
		
		//relocation ball
		trans._x -= 2.0 * collisionDist * rebound._x;
		trans._y -= 2.0 * collisionDist * rebound._y;
		
		orig._x = cosf(rotation) * trans._x - sinf(rotation) * trans._y;
		orig._y = sinf(rotation) * trans._x + cosf(rotation) * trans._y;
		
		ball.position = orig + position;
		
		return true;
	}
	
	
}

//Circle to Edge Collision Function aka Poly Collision for predicted_Trajectory
bool Peg::polyPegCollision_p(Ball &ball)
{
	GLfloat collisionDist = INFINITY;
	//bool isClosestEdge; 
	
	//Variables for edge collision
	Point2f vecFromVert;
	Point2f tangent, normal;
	GLfloat tangentComponent, normalComponent, edgeLenght;
	
	//Variables for Corner collision 
	
	int cornerIndex = -1, prevCornerIndex, nextCornerIndex;
	Point2f cornerNormal_1, cornerNormal_2;
	GLfloat cornerDist;
	
	//Variable for Rebound
	Point2f rebound;
	GLfloat orthogBallVelMag;
	GLfloat transPolyVelDotReb;
	
	//Calculate transformed co-ordinates from ball position
	Point2f orig(ball.position_p._x - position._x, ball.position_p._y - position._y);
	Point2f trans(cosf(rotation) * orig._x + sinf(rotation) * orig._y, 
	- sinf(rotation) * orig._x + cosf(rotation) * orig._y);
	
	//Calculate transformed co-ordinates from ball velocity
	
	Point2f transVel(cosf(rotation) * ball.position_p._x + sinf(rotation) * ball.position_p._y, 
	- sinf(rotation) * ball.position_p._x + cosf(rotation) * ball.position_p._y);
	
	//Calculate transformed co-ordinates from peg velocity...errr oh wait...it is zero!!
	Point2f zeroVeloc(0,0);
	Point2f transPegPolyVel(cosf(rotation) * zeroVeloc._x + sinf(rotation) * zeroVeloc._y, 
	- sinf(rotation) * zeroVeloc._x + cosf(rotation) * zeroVeloc._y);
	
	if(type == circle)
	{
		rebound = trans;
		collisionDist = rebound.magnitude()- ball.radius - vertices[0].magnitude();
		rebound.normalize();
	}
	else
	{
		//check Edge collision
		for(int i = 0; i < subs; i++)
		{
			//isClosestEdge = false;
			//Calculate vectFromVert 
			vecFromVert = trans - vertices[i];
			
			//Calculate tangent between two vertices
			tangent = vertices[i+1] - vertices[i];
			edgeLenght = tangent.magnitude();
			
			tangent.normalize();
			
			//calculate normal vector
			normal._x = tangent._y;
			normal._y = -tangent._x;
			
			//caluclate components
			tangentComponent = dotProduct(tangent, vecFromVert);
			normalComponent = dotProduct(normal, vecFromVert);
			
			if(normalComponent >= 0.0 && tangentComponent >= 0 && tangentComponent <= edgeLenght)
			{
			 //	isClosestEdge = true;
				collisionDist = normalComponent - ball.radius;
				rebound._x = normal._x;
				rebound._y = normal._y;
				
			}
			
		}
	}
	//if Edge don't collision and check corner collision
	
	if(collisionDist == INFINITY)
	{
		for(int i = 0; i < subs; i++)
		{
			Point2f cornerToBall;
			cornerToBall = trans - vertices[i];
			cornerDist = cornerToBall.magnitude() - ball.radius;
			
			if(cornerDist < collisionDist)
			{
				cornerIndex = i;
				nextCornerIndex = i + 1;
				if(i == 0)
					prevCornerIndex = subs - 1;
				else
					prevCornerIndex = i - 1;
				
				collisionDist = cornerDist;
				
				cornerToBall.normalize();
				rebound._x = cornerToBall._x;
				rebound._y = cornerToBall._y;
				
				//calculate cornerNomral_1 and cornerNomral_2
				if(dotProduct(rebound, transVel) > 0.0)
				{
					//check a segment line from current corner and previous corner
					cornerNormal_1 = vertices[cornerIndex] - vertices[prevCornerIndex];
					cornerNormal_1.normalize();
					
					//check a segment line from current corner and next corner
					cornerNormal_2 = vertices[cornerIndex] - vertices[nextCornerIndex];	
					cornerNormal_2.normalize();
					
					if(dotProduct(cornerNormal_1, transVel) < 0.0)
					{
						rebound = cornerNormal_1;
					}
					else if(dotProduct(cornerNormal_2, transVel) < 0.0)
					{
						rebound = cornerNormal_2;
					}
					else
					{
						rebound.reset();
						collisionDist = INFINITY;
					}				
				}
			}
		}
		//normalize rebound 
		rebound.normalize();
		
	}
	
	
	
	if(collisionDist > 0.0f)
	{
		return false;
	}
	else
	{
		//calcuate component that gets mirrored
		orthogBallVelMag= dotProduct(rebound, transVel);
		transVel._x -= 2.0f * orthogBallVelMag * rebound._x;
		transVel._y -= 2.0f * orthogBallVelMag * rebound._y;
		
		//calculate transVelocity
		transPolyVelDotReb = dotProduct(rebound, transPegPolyVel);
		transVel._x += transPolyVelDotReb * rebound._x;
		transVel._y += transPolyVelDotReb * rebound._y;
		
		//setting ball's velocity with new velocity
		ball.velocity_p._x = cosf(rotation) * transVel._x - sinf(rotation) * transVel._y;
		ball.velocity_p._y = sin(rotation) * transVel._x + cosf(rotation) * transVel._y;
		
		//relocation ball
		trans._x -= 2.0 * collisionDist * rebound._x;
		trans._y -= 2.0 * collisionDist * rebound._y;
		
		orig._x = cosf(rotation) * trans._x - sinf(rotation) * trans._y;
		orig._y = sinf(rotation) * trans._x + cosf(rotation) * trans._y;
		
		ball.position_p = orig + position;
		
		return true;
	}
	
	
}
