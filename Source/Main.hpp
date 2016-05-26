#pragma once
#define DEBUG
#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <vector>
#include "Point2f.hpp"
#include <cstdlib> 
//library from my code 
#include "Ball.hpp"
#include "Peg.hpp"
#include "Arena.hpp"
#include "Collisions.hpp"
//PolygonMode enum
typedef enum
{
	gl_line,
	gl_fill
	
}PolygonMode;

/* Basic camera struct */
typedef struct {
    bool rotating;
    bool zooming;
    float rotX, rotY;
    float zoom;
    float sensitivity;
    float lastMouseX;
    float lastMouseY;
} Camera;



/*Global variable structure*/
typedef struct
{
	int witdhOfWindow;
	int heightOfWindow;
	int tess; //tessellation
	float currentFramerate;
	float t;
	bool animate;
	float lastT;
	float deltTime;
	PolygonMode polygonMode;
	bool lighting;
	bool normal;
	bool isDisplayOSD;
	bool isPrintConsole;
	bool isFPS30;	
	bool isVisualDebug;
	bool isFire;
}Global;

void init();
void postRedisplay();
void reshape (int w, int h);
void display();


void renderingScene();
void renderingAllPeg();
void renderingAllBall();


void integrate();
void integrate(Ball &ball);
void update(float time);
bool handleEvents();
bool handleKeyDown(SDL_Keysym *key);
bool mouseDown(SDL_MouseButtonEvent *mouseEvent, bool pressure);
void mouseMotion(int x, int y);
void systemShutdown();


void collideParticlesWall();
void colliderBallFromPeg();
void predicted_Trajectory(Ball &master);
void printConsole();
bool collideParticleWall(Ball &b, Arena &a);
