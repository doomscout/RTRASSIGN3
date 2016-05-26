#pragma once
#include "Ball.hpp"
#include "Arena.hpp"
#include "Peg.hpp"
#include "Point2f.hpp"
#include "Main.hpp"

bool collideParticleWall_p(Ball &b, Arena &a);
bool colliderParticeCirclePeg(Ball &ball, Peg &peg, GLfloat time);
bool colliderConvertPoly();
bool collisionBoundingBox(Ball &ball, bool debugVisual, Peg &peg);
