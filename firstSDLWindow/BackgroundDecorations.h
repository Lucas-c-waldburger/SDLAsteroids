#pragma once
#include "CircleDraw.h"
#include "Time.h"
#include <random>

const int STAR_X_LINE_LENGTH = 6, STAR_Y_LINE_LENGTH = 8, STAR_DIAGONAL_LINE_LENGTH = 3;
const int ALPHA_MAX = 210, ALPHA_MIN = 20, ALPHA_CHANGE_RATE = 3;
const int NUM_STARS = 15, MIN_DISTANCE_BETWEEN_STARS = 55;

namespace BackgroundDecorations
{
	struct StarLine
	{
		StarLine();
		StarLine(LDPoint f, LDPoint s);

		LDPoint first, second;
		int alpha;
		bool fade;

		operator std::pair<LDPoint&, LDPoint&>();
		StarLine operator~() const;
	};  

	struct Star
	{
		Star(LDPoint center);

		SDL_Rect centerRect;
		StarLine lines[8];
		void draw(SDL_Renderer* renderer);
		void setShimmer(StarLine& l);

	};

	struct StarMaker
	{
		StarMaker(SDL_Renderer* renderer, int numStars);
		~StarMaker();

		std::vector<Star> stars;
		SDL_Renderer* pRenderer;

		void drawAll();
		void randomizeStarLocations(int numStars);

	};


};

