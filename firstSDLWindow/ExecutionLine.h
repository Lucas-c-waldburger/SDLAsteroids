#pragma once
#include "TextTexture.h"

const int EXLINE_XPOS = 150, EXLINE_YPOS = 70, EXLINE_WIDTH = SCREEN_WIDTH - 300, EXLINE_HEIGHT = 50;
const Position EXLINE_TRIGGER_POS = { EXLINE_XPOS + (EXLINE_WIDTH / 2), EXLINE_YPOS + (EXLINE_HEIGHT / 2) };


class ExecutionLine
{
public:
	ExecutionLine(RenderWrap& renderer, SDL_Color filledCol, SDL_Color borderCol, int xPos, int yPos, int w, int h);

	Traits filledTraits, borderTraits;

	void draw();


private:
	TextTexture txt;
	SDL_Rect filledRect;
	SDL_Rect borderRect;
	RenderWrap& renderer;

};

