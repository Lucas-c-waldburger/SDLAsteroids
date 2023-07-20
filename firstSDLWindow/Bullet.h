#pragma once
#include "Utils.h"


// bullets get initialized with forwardPathProjection passed by value
// bullets ho
using namespace Utils;

const int BULLET_HEIGHT = 5, BULLET_WIDTH = 5;

struct Bullet : public SDL_Rect
{
	Bullet(std::vector<LDPoint> currentForwardPathProjection);

	std::vector<LDPoint> forwardPathProjection;
	int pathIndex;
	bool active;

	void updateRectXY();
};

struct BulletGenerator
{
	BulletGenerator(SDL_Renderer*& pRenderer);
	std::vector<Bullet> bullets;
	SDL_Renderer*& pRendererRef;

	void makeBullet(std::vector<LDPoint> currentForwardPathProjection);
	void drawAll();
};