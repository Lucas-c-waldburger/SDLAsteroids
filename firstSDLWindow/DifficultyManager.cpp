#include "DifficultyManager.h"

DifficultyManager::DifficultyManager() : scoreTierCurrentIndex(0)
{
	int scoreTier = 1;
	std::generate(scoreTierCutoffs, scoreTierCutoffs + NUM_SCORE_TIERS, [&scoreTier]() { scoreTier += SCORE_TIER_AMOUNT; return scoreTier; });
}

void DifficultyManager::handleDifficulty(AsteroidGenerator& asteroidGenerator, ScoreDisplay::ScoreBoard& scoreBoard)
{
	if (shouldIncreaseDifficulty(scoreBoard.getTotalScore()))
	{
		asteroidGenerator.waitBetweenSpawn -= ASTEROID_SPAWN_DELAY_DECREMENT;
		asteroidGenerator.maxAsteroidsOnScreen += ASTEROID_MAX_INCREMENT;
		++scoreTierCurrentIndex;
	}
}

bool DifficultyManager::shouldIncreaseDifficulty(int currentScore)
{
	return (scoreTierCurrentIndex < NUM_SCORE_TIERS) && (currentScore >= scoreTierCutoffs[scoreTierCurrentIndex]);	
}

