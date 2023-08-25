#pragma once

#include "Asteroid.h"
#include <iostream>
#include <unordered_map>


namespace ScoreDisplay
{
    const int SEGMENT_LENGTH = 17, PADDING = 15;
    constexpr int X_SHIFT_FOR_TENS = SEGMENT_LENGTH + PADDING;

    extern const LDPoint SEG_POINTS[6];
    extern const std::pair<LDPoint, LDPoint> SEG_PAIRS[7];
    extern std::unordered_map<int, std::vector<std::pair<LDPoint, LDPoint>>> numberMap;


    class ScoreBoard
    {
    public:
        ScoreBoard(SDL_Renderer* renderer);
        ~ScoreBoard();

        const int getTotalScore();
        void setTotalScore(int newScore);

        void draw();


    private:
        SDL_Renderer* pRenderer;

        int totalScore;
        std::pair<int, int> separateScore();


    };


}

