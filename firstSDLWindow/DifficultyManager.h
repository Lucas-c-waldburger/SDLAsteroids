#pragma once
#include "ScoreDisplay.h"

const int ASTEROID_SPEED_UP_INCREMENT = 1, ASTEROID_MAX_INCREMENT = 3, ASTEROID_SPAWN_DELAY_DECREMENT = 140;
const int NUM_SCORE_TIERS = 14, SCORE_TIER_AMOUNT = 7;

class DifficultyManager
{
public:
	DifficultyManager();

	void handleDifficulty(AsteroidGenerator& asteroidGenerator, ScoreDisplay::ScoreBoard& scoreBoard);
	bool shouldIncreaseDifficulty(int currentScore);

private:

	int scoreTierCutoffs[NUM_SCORE_TIERS];
	int scoreTierCurrentIndex;


};

