#include "CInscribedTriangle.h"

CInscribedTriangle::CInscribedTriangle(SDL_Renderer* renderer, int r, LDPoint c) : CircleDraw(renderer, r, c)
{
	
	sortPerimeterPoints();
	move(center);

	trianglePointIndexes.reserve(3);

	assignTrianglePointIndexes();

}

void CInscribedTriangle::draw()
{
	SDL_SetRenderDrawColor(rendererCpy, 0, 0, 0 , 0xFF);

	SDL_RenderDrawLine(rendererCpy, perimeterPoints[trianglePointIndexes[0]].x, perimeterPoints[trianglePointIndexes[0]].y,
		perimeterPoints[trianglePointIndexes[1]].x, perimeterPoints[trianglePointIndexes[1]].y);

	SDL_RenderDrawLine(rendererCpy, perimeterPoints[trianglePointIndexes[1]].x, perimeterPoints[trianglePointIndexes[1]].y,
		perimeterPoints[trianglePointIndexes[2]].x, perimeterPoints[trianglePointIndexes[2]].y);

	SDL_RenderDrawLine(rendererCpy, perimeterPoints[trianglePointIndexes[2]].x, perimeterPoints[trianglePointIndexes[2]].y,
		perimeterPoints[trianglePointIndexes[0]].x, perimeterPoints[trianglePointIndexes[0]].y);

}

void CInscribedTriangle::rotate(int amount)
{
	int ppSize = perimeterPoints.size() - 1;
	for (int& tpi : trianglePointIndexes)
	{
		int projected = (tpi + amount) % ppSize;
		
		if (projected < 0)
			projected += ppSize;

		tpi = projected;

		std::cout << "AFTER: " << tpi << '\n';

	}

}

void CInscribedTriangle::sortPerimeterPoints()
{
	std::vector<LDPoint> temp;
	temp.reserve(perimeterPoints.size());

	std::copy_if(perimeterPoints.begin(), perimeterPoints.end(), std::back_inserter(temp), [](LDPoint& p)
		{
			return p.x <= 0;
		});

	std::stable_sort(temp.begin(), temp.end(), [](const LDPoint& p1, const LDPoint& p2)
		{
			return p1.x < p2.x;
		});

	auto posYs1 = std::stable_partition(temp.begin(), temp.end(), [](LDPoint& p)
		{
			return p.y <= 0;
		});

	std::reverse(temp.begin(), posYs1);

	perimeterPoints = temp;

	std::transform(++temp.begin(), --temp.end(), std::back_inserter(perimeterPoints), [](LDPoint& p)
		{
			p.x = -p.x; p.y = -p.y;
			return p;
		});
}

void CInscribedTriangle::assignTrianglePointIndexes()
{
	int size = perimeterPoints.size();
	trianglePointIndexes = { size - 1, static_cast<int>(size * 0.33), static_cast<int>(size * 0.66) };
	//trianglePointIndexes.push_back(perimeterPoints.size() - 1);
	//trianglePointIndexes.push_back(perimeterPoints.size() * 0.33);
	//trianglePointIndexes.push_back(perimeterPoints.size() * 0.66);


}

void CInscribedTriangle::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
			case SDLK_a:
				rotate(2);
				break;

			case SDLK_d:
				rotate(-2);
				break;
		}
	}
}
