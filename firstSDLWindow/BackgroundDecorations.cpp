#include "BackgroundDecorations.h"


BackgroundDecorations::StarLine::StarLine() : alpha(255), fade(true)
{}

BackgroundDecorations::StarLine::StarLine(LDPoint f, LDPoint s) : first(f), second(s), alpha(255), fade(true)
{}

BackgroundDecorations::StarLine BackgroundDecorations::StarLine::operator~() const 
{
	return { second, first };
}

BackgroundDecorations::StarLine::operator std::pair<LDPoint&, LDPoint&>()
{
	return std::pair<LDPoint&, LDPoint&>(first, second);
}



BackgroundDecorations::Star::Star(LDPoint center)
{
	// horizontal lines
	lines[0] = { { center.x - STAR_X_LINE_LENGTH, center.y }, center };
	lines[1] = ~lines[0]; lines[1].second.x += STAR_X_LINE_LENGTH * 2;

	// vertical lines
	lines[2] = { { center.x, center.y - STAR_Y_LINE_LENGTH }, center };
	lines[3] = ~lines[2]; lines[3].second.y += STAR_Y_LINE_LENGTH * 2;

	// top-left to bot-right lines
	lines[4] = { { center.x - STAR_DIAGONAL_LINE_LENGTH, center.y - STAR_DIAGONAL_LINE_LENGTH }, center };
	lines[5] = ~lines[4]; lines[5].second += (STAR_DIAGONAL_LINE_LENGTH * 2);

	// bot-left to top-right lines
	lines[6] = { { center.x - STAR_DIAGONAL_LINE_LENGTH, center.y + STAR_DIAGONAL_LINE_LENGTH }, center };
	lines[7] = ~lines[6]; lines[6].second.x += (STAR_DIAGONAL_LINE_LENGTH); lines[6].second.y -= (STAR_DIAGONAL_LINE_LENGTH);

	
	int startingAlpha;
	std::for_each(lines, lines + 8, [&startingAlpha](StarLine& l)
		{
			startingAlpha = (rand() % 141) + 80;
			l.alpha = startingAlpha;
		});

	centerRect = { center.x - 1, center.y - 1, 3, 3 };

}

void BackgroundDecorations::Star::draw(SDL_Renderer* renderer)
{
	
	std::for_each(lines, lines + 7, [&](BackgroundDecorations::StarLine& l) 
		{ 
			setShimmer(l);
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, l.alpha);
			SDL_RenderDrawLine(renderer, l.first.x, l.first.y, l.second.x, l.second.y); 
		});
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &centerRect);
}

void BackgroundDecorations::Star::setShimmer(StarLine& l)
{
	if (l.fade)
	{
		l.alpha -= ALPHA_CHANGE_RATE;
		if (l.alpha <= ALPHA_MIN)
		{
			l.alpha = ALPHA_MIN;
			l.fade = false;
		}
	}
	else
	{
		l.alpha += ALPHA_CHANGE_RATE;
		if (l.alpha >= ALPHA_MAX)
		{
			l.alpha = ALPHA_MAX;
			l.fade = true;
		}
	}
}

BackgroundDecorations::StarMaker::StarMaker(SDL_Renderer* renderer, int numStars) : pRenderer(renderer)
{
	randomizeStarLocations(numStars);
}

BackgroundDecorations::StarMaker::~StarMaker()
{
	pRenderer = nullptr;
}

void BackgroundDecorations::StarMaker::drawAll()
{
	for (auto& star : stars)
		star.draw(pRenderer);
}

void BackgroundDecorations::StarMaker::randomizeStarLocations(int numStars = 15)
{
	auto randLoc = []() { return LDPoint{ (rand() % SCREEN_WIDTH), (rand() % SCREEN_HEIGHT) }; };
	auto dist = [](const Star& s, const LDPoint& p)
	{
		int xDiff = p.x - (s.centerRect.x + (s.centerRect.w / 2));
		int yDiff = p.y - (s.centerRect.y + (s.centerRect.h / 2));
		return (xDiff * xDiff) + (yDiff + yDiff);
	};

	bool validLoc;
	LDPoint newLoc;

	stars.emplace_back(randLoc());

	for (int i = 1; i < numStars; i++)
	{
		do
		{
			validLoc = true;
			newLoc = randLoc();
			for (auto& star : stars)
			{
				if (dist(star, newLoc) < (MIN_DISTANCE_BETWEEN_STARS * MIN_DISTANCE_BETWEEN_STARS))
				{
					validLoc = false;
					break;
				}
			}
		} while (!validLoc);

		stars.emplace_back(newLoc);
	} 
}

