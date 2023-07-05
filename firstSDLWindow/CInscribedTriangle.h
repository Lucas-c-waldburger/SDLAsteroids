#pragma once
#include "CircleDraw.h"

class CInscribedTriangle : public CircleDraw
{
public:
	CInscribedTriangle(SDL_Renderer* renderer, int r, LDPoint c);

	void draw();
	void rotate(int amount);

	std::vector<int> trianglePointIndexes;

	void sortPerimeterPoints();
	void assignTrianglePointIndexes();

	void handleEvent(SDL_Event* e);

private:
};

