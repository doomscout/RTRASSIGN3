#include "Collisions.hpp"


//Ball to Wall Collision for predicted_Trajectory 
bool collideParticleWall_p(Ball &b, Arena &a)
{
	
	
	float dp[2];
	dp[0] = dp[1] = 1.0;
	
	if ((b.position_p._x - b.radius) < a.min._x) 
	{
		b.position_p._x += 2.0 * (a.min._x - (b.position_p._x- b.radius));
		b.velocity_p._x *= -1.0;
		dp[0] += b.mass * -2.0 * b.velocity._x;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];

		return true;
    }
    
	if ((b.position_p._y - b.radius) < a.min._y) 
	{
		b.position_p._y += 2.0 * (a.min._y - (b.position_p._y - b.radius));
		b.velocity_p._y *= -1.0;
		dp[1] += b.mass * -2.0 * b.velocity_p._y;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];

		return true;
	}
	
	if ((b.position_p._x + b.radius) > a.max._x) 
	{
		b.position_p._x -= 2.0 * (b.position_p._x + b.radius - a.max._x);
		b.velocity_p._x *= -1.0;
		dp[0] += b.mass * -2.0 * b.velocity_p._x;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];

		return true;
	}
	
	if ((b.position_p._y + b.radius) > a.max._y) 
	{
		b.position_p._y -= 2.0 * (b.position_p._y + b.radius - a.max._y);
		b.velocity_p._y *= -1.0;
		dp[1] += b.mass * -2.0 * b.velocity_p._y;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];

		return true;
	}
	//The damp shuold be here, only on collision, 

	return false;
}


bool colliderParticeCirclePeg(Ball &ball, Peg &peg, GLfloat time)
{
	
	
	GLfloat sum_radii, sum_radii_sq, n_mag_sq;
	Point2f normal;
	
	normal = ball.position - peg.position;
	//GLfloat distance = normal.magitude();
	
	sum_radii = ball.radius + peg.radius;
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
			
			ball.position._x += 2.0f * (sum_radii - peg.radius + ball.radius) * normal._x * time;
			ball.position._y += 2.0f * (sum_radii - peg.radius + ball.radius) * normal._y * time;
			
		}
		
		return true;
	}
	else 
	{
		return false;	
	}
	
}
bool collisionBoundingBox(Ball &ball, bool debugVisual, Peg &peg)
{
	GLfloat collisionDist = INFINITY;
	GLfloat cornerDist;
	int cornerIndex = -1;
	
	Point2f *vertices = new Point2f[5];
	vertices[0].setXY(peg.radius + peg.position._x, peg.radius + peg.position._y);
	vertices[1].setXY(peg.radius + peg.position._x, -peg.radius + peg.position._y);
	vertices[2].setXY(-peg.radius + peg.position._x, -peg.radius + peg.position._y);
	vertices[3].setXY(-peg.radius + peg.position._x, peg.radius +  peg.position._y);
	vertices[4].setXY(peg.radius + peg.position._x, peg.radius + peg.position._y);
	
	Point2f * orthogVecs = new Point2f[4];
	orthogVecs[0].setXY(1.0, 0.0);
	orthogVecs[0].setXY(0.0, -1.0);
	orthogVecs[0].setXY(-1.0, 0.0);
	orthogVecs[0].setXY(0.0, 1.0);
	
	//Vector parallel to hit box edge remainder;
	Point2f hitRemaidner;
	
	//Component orthogonal to hit box edge
	GLfloat orthogDist;
	
	//Component paraell to hit box edge
	GLfloat hitRemainderDist;
	
	//Caluclate the ball's position in transformed co-ordinates
	Point2f orig(ball.position._x - peg.position._x, ball.position._y - peg.position._y);
	
	Point2f trans(cosf(peg.rotation) * orig._x + sinf(peg.rotation) * orig._y, 
	-sin(peg.rotation) * orig._x + cosf(peg.rotation) * orig._y);
	
	for(int i = 0; i < 4; i++)
	{
		orthogDist = dotProduct(orthogVecs[i], trans);
		hitRemaidner._x = trans._x - orthogDist * orthogVecs[i]._x;
		hitRemaidner._y = trans._y - orthogDist * orthogVecs[i]._y;
		hitRemainderDist = hitRemaidner.magnitude();
		//std::cout << "hitRemainderDist : "<<  hitRemainderDist << std::endl;
		//std::cout << "peg.Radius : "<<  peg.radius << std::endl;
		if(orthogDist >= 0.0 && hitRemainderDist <= peg.radius)
		{
			
			glColor3f(1.0f, 0.0f, 0.0f);
			collisionDist = orthogDist - (peg.radius + ball.radius);
		}
		else
		{
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		
		if(debugVisual)
		{
			glBegin(GL_LINES);
			glVertex2f(vertices[i]._x, vertices[i]._y);
			glVertex2f(vertices[i+1]._x, vertices[i+1]._y);
			glEnd();
		}		
		
	}
	/*check Corners */
	if(collisionDist == INFINITY)
	{
		for(int i = 0; i < 4; i++)
		{
			cornerDist = sqrt((trans._x - vertices[i]._x) 
			* (trans._x - vertices[i]._x) + (trans._y - vertices[i]._y)
			* (trans._y - vertices[i]._y)) - ball.radius;
			
			if(cornerDist < collisionDist)
			{
				cornerIndex = i;
				collisionDist = cornerDist;
			}			
		}
		
		if(debugVisual)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glPointSize(3);
			glBegin(GL_POINTS);
			glVertex2f(vertices[cornerIndex]._x, vertices[cornerIndex]._y);
			glEnd();
		}
		
	}
//	std::cout << "collisionDist : "<<  collisionDist << std::endl;
	if(collisionDist > 0.0)
		return false;
	else
		return true;

}

bool colliderConvertPoly()
{
	return true;
}




