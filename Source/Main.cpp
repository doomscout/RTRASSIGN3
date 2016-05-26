#include "Main.hpp"


using namespace std;

GLfloat prevTime = 0;
static int wantRedisplay = 1;
static SDL_Window *mainWindow = 0;
bool exit_main = false;
Camera camera = {false,false,0,0, 1.0f,0.3f,0,0};
Global g = {800, 800,32, 0.0f, 0.0f, true, 0,0, gl_line, false, false, true, false, false, false, false};

//const float FacSpeed = 0.0000001;
const float FacSpeed = 0.001;
const GLfloat gravity = -9.8;
const int ballSize = 1;
const int pegSize = 36;
Ball b;
Arena a;
Peg * peg = new Peg[pegSize];
static int predictStep = 0;
int main()
{
	int argc = 0;   
    char *argv = "";
    glutInit(&argc, &argv);
	init();
   /*Initialization SDL2 setting*/	
 	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		return EXIT_SUCCESS;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	

	mainWindow = SDL_CreateWindow("Assignment3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g.witdhOfWindow, g.heightOfWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!mainWindow)
	{
		fprintf(stderr, "Failed to create a window: %s\n", SDL_GetError());
		return EXIT_SUCCESS;
	}		
	SDL_GLContext mainGLContext = SDL_GL_CreateContext(mainWindow);
	SDL_GL_MakeCurrent(mainWindow, mainGLContext);
	reshape(g.witdhOfWindow, g.heightOfWindow);
	
	//initization material and lighting
	glClearColor(0, 0, 0, 0);
	bool loop = true;
	
	
	//Event Loop
	while(loop)
	{
		g.deltTime = SDL_GetTicks() - prevTime;
		prevTime =  SDL_GetTicks();
	//	cout << "deltTime: " << g.deltTime << endl;
		handleEvents();
		    
		if (wantRedisplay) {
			display();
	
				
			wantRedisplay = 0;
		}
		update(g.deltTime * 0.001);
		
		if(exit_main)
		{
			loop = false;
		}		
	}
	
	
	atexit(systemShutdown);

	return EXIT_SUCCESS;
}

void init()
{
	

	cout << "initzation" << endl;
	b.initPlacement( 0, 90);

	
	#if 0
	for(int i = 0; i < pegSize / 4; i++)
	{
		cout << "initzation" << endl;
		peg[i].initPlacement(12 * i, 0, hexagon, 4);
		peg[i].initPlacement(12 * i, -20, triangle, 4);
		peg[i].initPlacement(12 * i, -40, circle, 4);
		peg[i].initPlacement(12.5 * i, -60, pentagon, 4);
		
	}
	#endif
	int i = 0;
	GLfloat rotation = 0.0f;
	GLfloat x = -80;
	while(i < pegSize)
	{
		peg[i++].initPlacement(x, 0, hexagon, 4,rotation );
		rotation += 0.5f;
		peg[i++].initPlacement(x, -20, triangle, 4, rotation);
		rotation += 0.5f;
		peg[i++].initPlacement(x, -40, circle, 4, rotation);
		rotation += 0.5f;
		peg[i++].initPlacement(x, -60, pentagon, 4, rotation);
		x+= 20;
	}
	
	//b[0].initPlacement(1, 1);
	//b[1].initPlacement(2, 2);
}


void postRedisplay()
{
  wantRedisplay = 1;
}

//Modifty/Change window size function
void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
 // gluPerspective(100.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 // glTranslatef (0.0, 0.0, -5.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glEnable(GL_DEPTH_TEST);
	
	if(g.polygonMode == gl_line)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, g.witdhOfWindow, g.heightOfWindow);
	glPushMatrix();
	if(!g.isFire)
	{
		predicted_Trajectory(b);
		//b[0].printVelocity();
	}
	else
	{
		//Brute Force Collider
		collideParticlesWall();
		colliderBallFromPeg();
	}
	
	//Rendering everything
	renderingScene();
	

	glPopMatrix();
	SDL_GL_SwapWindow(mainWindow);
}

//Rendering everything in a scene function
void renderingScene()
{		
	if(g.isFire)
		integrate();
		
	renderingAllPeg();
	renderingAllBall();
	a.displayArena();
	if(g.isPrintConsole)
		printConsole();
	
}

//Rendering all Peg in a scene function
void renderingAllPeg()
{
	for(int i = 0; i < pegSize; i++)
	{
		if(peg[i].hp > 0)
		{
			glPushMatrix();
			peg[i].RenderPeg(1,1,1);
			glPopMatrix();
		}
	}
}

//Rendering all ball in a scene function
void renderingAllBall()
{

		glPushMatrix();
		glTranslatef(b.position.getX(), b.position.getY(), 0.0); 
		b.displayParticle(1,1,1);
		glPopMatrix();
		//cout << "Ball X :" << b[i].position.getX() << " Ball Y :"  <<   b[i].position.getY() << endl;
	
}

// Integrate equations of motion predicted
void integrate()
{

	float t = g.deltTime * 0.001;
	//cout << "time :" << t << endl;

	
		b.velocity += b.acceleration * t;
		//b[i].printVelocity();
		b.velocity *= pow(b.damp, t);
		b.position += b.velocity * t ;
		predictStep++;
		//cout << "predictStep  :" << predictStep << endl;
}

// Integrate equations of motion for clone ball under 
void integrate(Ball &ball)
{

	float t = g.deltTime * 0.001;
	//cout << "time :" << t << endl;

	
		ball.velocity_p += ball.acceleration * t;
		ball.velocity_p *= pow(ball.damp, t);
		ball.position_p += ball.velocity_p * t ;


}

//Update time for animation function
void update(float time)
{
	float dt;
	//const float fps 30
	const float fps30 = 30.0f;
	/* Update positions here */
    static float fpsTime = 0.0f;
    static int fpsFrames = 0;
    
    //30 fps mode
    /**
     * 1 second = 1000 millisecond = 1 000 000 000 nanosecond
     * 1 millisecond = 1 000 000 nanosecond
     * http://timmurphy.org/2009/09/29/nanosleep-in-c-c/
     */
     //store as nanosecond format
    static long sleepTime = 0; 
    
    struct timespec delay;
		if(g.isFPS30)
		{
			//calucation under millisecond format and 
			// to get FrameTime around 31 to 32 in frame/millseconds after reach on 30 fps
			long calucFrameTime = (sleepTime / 1000000L) + (1000.0f / fps30)
		                             - (time * 1000.0f);
		    //  cout << "calucMax" << calucFrameTime << endl;
		 
		 //convert To Nanosecond format from millisecond for return value on sleepTime
		     sleepTime = fmax(0.0f, calucFrameTime) * 1000000L;
		     delay.tv_sec = 0;
		     delay.tv_nsec = sleepTime;
		     nanosleep(&delay, (struct timespec*)NULL);
		 }
		 
    //animating
	if(g.animate)
	{
		dt = time - g.lastT;
		g.t += dt;
		
	}
    	
	fpsTime += time;
	fpsFrames += 1;
	
	//calucation frame per seconds
    if (fpsTime > 1.0f) {
        g.currentFramerate = fpsFrames / fpsTime;
        fpsTime = 0.0f;
        fpsFrames = 0;
    }
	postRedisplay();
}

//SDL2 event Dispatcher Function
bool handleEvents()
{
	static int lastX = 0;
    static int lastY = 0;
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(EXIT_SUCCESS);
		case SDL_MOUSEMOTION:
			lastX = event.motion.x;
			lastY = event.motion.y;
			mouseMotion(lastX,lastY);
			postRedisplay();
			break;
		case SDL_MOUSEBUTTONDOWN:
			//cout << "left mouseClick" << endl;
			//return true;
			if(mouseDown(&event.button, true))
			postRedisplay();
			break;
		case SDL_MOUSEBUTTONUP:
			if(mouseDown(&event.button, false))
			postRedisplay();
			break;
		case SDL_KEYDOWN:
			if (handleKeyDown(&event.key.keysym))
			{
				postRedisplay();
			}
			return true;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				if (event.window.windowID == SDL_GetWindowID(mainWindow))
				{
					SDL_SetWindowSize(mainWindow, event.window.data1, event.window.data2);
					reshape(event.window.data1, event.window.data2);
					g.witdhOfWindow = event.window.data1;
					g.heightOfWindow = event.window.data2;
					postRedisplay();
				};
				break;
			case SDL_WINDOWEVENT_CLOSE:
				return true;
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	return false;
}


bool handleKeyDown(SDL_Keysym *key)
{
	/* Handle key press events here */
	switch (key->sym)
	{
	case SDLK_ESCAPE:
		exit_main = true;
		return true;
		break;

	/*Animation hotkey*/
/*
	case 'a':
		g.animate = !g.animate;
		return true;
		break;	
*/
	case 'c':
		g.isPrintConsole = !g.isPrintConsole;
		return true;
		break;	
/*
	case 'f':
		g.isFPS30 = !g.isFPS30;
		return true;
		break;	
*/		
	case 'd':
		g.isVisualDebug = !g.isVisualDebug;
		return true;
		break;	
		
	case 'v':
		g.isFire = !g.isFire;
		return true;
		break;
		
	case SDLK_LEFT:
	    b.velocity._x -= 1.0;
	    if(b.velocity._x < -20)
			b.velocity._x = -20;
	    return true;
	    break;
	    
	     	

	case SDLK_RIGHT:
		b.velocity._x += 1.0;
	    if(b.velocity._x > 20)
			b.velocity._x = 20;
			
	    return true;
		break;
	default:
	break;
	
     }
     return false;
}

//Press Mouse button function
bool mouseDown(SDL_MouseButtonEvent *mouseEvent, bool pressure)
{
	switch(mouseEvent->button)
	{
		case SDL_BUTTON_LEFT:
		if(pressure)
		{
			camera.rotating = pressure;
			#if 0
			cout << "Pressured right" << endl;
			#endif
		}
		else
		{
			camera.rotating = pressure;
			#if 0
			cout << "Release" << endl;
			#endif
		}
		return true;
		break;
		
		case SDL_BUTTON_RIGHT:
		if(pressure)
		{
			camera.zooming = pressure;
			#if 0
			cout << "Pressure left" << endl;
			#endif
		}
		else
		{
			camera.zooming = pressure;
			#if 0
			cout << "Release" << endl;
			#endif
		}
		return true;
		break;
	}
	return false;
}

//mouse motion function
void mouseMotion(int x, int y)
{
	int dx = x - camera.lastMouseX;
    int dy = y - camera.lastMouseY;

    if (camera.rotating) {
        camera.rotY += dx * camera.sensitivity;
        camera.rotX += dy * camera.sensitivity;
    }
    
    if(camera.zooming)
    {
		camera.zoom += dy * camera.sensitivity * .1f;
	}
    camera.lastMouseX = x;
    camera.lastMouseY = y;
}

void systemShutdown()
{
	SDL_Quit();
}

//BruteForce Ball to Walls collision
void collideParticlesWall()
{
  
    collideParticleWall(b, a);
  
}
//BruteForce Ball to Peg collision
void colliderBallFromPeg()
{
		for(int j = 0; j < pegSize; j++)
		{

			#if 1
				
			if(peg[j].hp > 0)
			{
				if(peg[j].polyPegCollision(b, g.isVisualDebug))
				{
					if(!g.isVisualDebug)
						peg[j].FlashColor();
				
					peg[j].hp--;
				//	cout << " collider!" << endl;
				}
				else
				{
					peg[j].FadeColor(g.deltTime);
					//cout << " NO !" << endl;
				}
			}
			#endif
		//circlePegCollision
		
	}

}

//predicted_Trajectory Function 
void predicted_Trajectory(Ball &master)
{
	//Clone ball but don't display
	Point2f * newValue = new Point2f[2];
	newValue[0] = master.position;
	newValue[1] = master.velocity;
	master.position_p = newValue[0];
	master.velocity_p = newValue[1]; 
	
	int collisonDone = 0;
	int step = 0;
	#if 1
	//vector for store movement clone's position
	vector<Point2f> stored;
	stored.push_back(master.position_p);
	//start Loop until collisionDone
	while( step < 500)
	{
		
		#if 1
		if(collideParticleWall_p(master, a))
			collisonDone++;
		
		for(int i = 0; i < pegSize; i++)
		{
			if(peg[i].hp > 0)
			{
				if(peg[i].polyPegCollision_p(master))
					collisonDone++;
			}
		}
		#endif
		integrate(master);
		stored.push_back(master.position_p);
		step++;
	}
	
	glColor3f(0,0,1);
	glBegin(GL_POINTS);			
	for(unsigned int j = 0; j < stored.size(); j++)
	{
		glVertex2f(stored[j]._x,
				   stored[j]._y);
	}
	glEnd();
	
	stored.clear();
	#endif
}
void printConsole()
{
	cout << "Frame per Seconds: " << g.currentFramerate << endl;	
}

//Ball to Wall Collision from Lab sample code
bool collideParticleWall(Ball &b, Arena &a)
{
	
	
	float dp[2];
	dp[0] = dp[1] = 1.0;
	
	if ((b.position._x - b.radius) < a.min._x) 
	{
		b.position._x += 2.0 * (a.min._x - (b.position._x- b.radius));
		b.velocity._x *= -1.0;
		dp[0] += b.mass * -2.0 * b.velocity._x;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];

		return true;
    }
    
	if ((b.position._y - b.radius) < a.min._y) 
	{
	//	b.position._y += 2.0 * (a.min._y - (b.position._y - b.radius));
	//	b.velocity._y *= -1.0;
	//	dp[1] += b.mass * -2.0 * b.velocity._y;
	//	a.momentum._x += dp[0];
	//	a.momentum._y += dp[1];
		
		b.initPlacement( 0, 90);
		g.isFire = false;
		return true;

	}
	
	if ((b.position._x + b.radius) > a.max._x) 
	{
		b.position._x -= 2.0 * (b.position._x + b.radius - a.max._x);
		b.velocity._x *= -1.0;
		dp[0] += b.mass * -2.0 * b.velocity._x;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];
		return true;		
	}
	
	if ((b.position._y + b.radius) > a.max._y) 
	{
		b.position._y -= 2.0 * (b.position._y + b.radius - a.max._y);
		b.velocity._y *= -1.0;
		dp[1] += b.mass * -2.0 * b.velocity._y;
		a.momentum._x += dp[0];
		a.momentum._y += dp[1];
		return true;
	}
	//The damp shuold be here, only on collision, 

	return false;
}

