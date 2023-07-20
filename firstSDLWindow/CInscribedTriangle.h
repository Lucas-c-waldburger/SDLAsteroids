#pragma once
#include "CircleDraw.h"
#include "Bullet.h"

const int PIXELS_MOVE_PER_FRAME = 3, ROTATION_RATE = 2;

// PROBABLY RIP ALL MATH OUT OF THESE AND MAKE A TRUE BASE CLASS OUT OF THE ORIGINAL PERIMTER FINDING
class CInscribedTriangle : public CircleDraw
{
public:

	CInscribedTriangle(SDL_Renderer* renderer, int r, LDPoint c);

	BulletGenerator bulletGenerator;

	void draw();
	void rotate(int amount);
	void goForward();
	void shoot();


	void sortPerimeterPoints();
	void assignTrianglePointIndexes();
	void generateForwardPathPoints();

	// MOVE THESE TWO FUNCS TO UTILS
	LDPoint extendLinePoint(LDPoint& A, LDPoint& B, int distance);
	bool pointWithinBounds(LDPoint& p);

	void handleEvent(SDL_Event* e);
	void handleKeyStates(const Uint8*& keystates);

private:
	LDPoint trianglePoints[4];
	std::vector<int> trianglePointIndexes;
	std::vector<LDPoint> forwardPathPoints;

	

	bool facingNewDirection;
	int currentForwardPathIndex;

	void updateTranglePoints();
};

