#include "ScoreDisplay.h"

ScoreDisplay::ScoreBoard::ScoreBoard(SDL_Renderer* renderer) : pRenderer(renderer), totalScore(0)
{};


ScoreDisplay::ScoreBoard::~ScoreBoard()
{
    pRenderer = nullptr;
}


const int ScoreDisplay::ScoreBoard::getTotalScore()
{
    return totalScore;
}


void ScoreDisplay::ScoreBoard::setTotalScore(int newScore)
{
    totalScore = newScore;
}


std::pair<int, int> ScoreDisplay::ScoreBoard::separateScore()
{
    return std::make_pair((totalScore / 10) % 10, totalScore % 10);
}


void ScoreDisplay::ScoreBoard::draw()
{
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    std::pair<int, int> separatedScore = separateScore();
    
    for (auto& seg : ScoreDisplay::numberMap[separatedScore.first])
    {
        SDL_RenderDrawLine(pRenderer, seg.first.x - X_SHIFT_FOR_TENS, seg.first.y, seg.second.x - X_SHIFT_FOR_TENS, seg.second.y);
    }
    
    for (auto& seg : ScoreDisplay::numberMap[separatedScore.second])
    {
        SDL_RenderDrawLine(pRenderer, seg.first.x, seg.first.y, seg.second.x, seg.second.y);
    }
}


const LDPoint ScoreDisplay::SEG_POINTS[6] =
{
    {SCREEN_WIDTH - SEGMENT_LENGTH - PADDING, PADDING},
    {SCREEN_WIDTH - PADDING, PADDING},
    {SCREEN_WIDTH - PADDING, SEGMENT_LENGTH + PADDING},
    {SCREEN_WIDTH - PADDING, (SEGMENT_LENGTH * 2) + PADDING},
    {SCREEN_WIDTH - SEGMENT_LENGTH - PADDING, (SEGMENT_LENGTH * 2) + PADDING},
    {SCREEN_WIDTH - SEGMENT_LENGTH - PADDING, SEGMENT_LENGTH + PADDING}
};


const std::pair<LDPoint, LDPoint> ScoreDisplay::SEG_PAIRS[7] =
{
    { SEG_POINTS[0], SEG_POINTS[1] }, // TOP       [0]
    { SEG_POINTS[1], SEG_POINTS[2] }, // TOP-RIGHT [1]
    { SEG_POINTS[2], SEG_POINTS[3] }, // BOT-RIGHT [2]
    { SEG_POINTS[3], SEG_POINTS[4] }, // BOT       [3]
    { SEG_POINTS[4], SEG_POINTS[5] }, // BOT-LEFT  [4]
    { SEG_POINTS[5], SEG_POINTS[0] }, // TOP-LEFT  [5]
    { SEG_POINTS[5], SEG_POINTS[2] }, // MID       [6]
};


std::unordered_map<int, std::vector<std::pair<LDPoint, LDPoint>>> ScoreDisplay::numberMap =
{
    { 0, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[4], SEG_PAIRS[5] } },
    { 1, { SEG_PAIRS[1], SEG_PAIRS[2] } },
    { 2, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[6], SEG_PAIRS[4], SEG_PAIRS[3] } },
    { 3, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[6] } },
    { 4, { SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[6], SEG_PAIRS[5] } },
    { 5, { SEG_PAIRS[0], SEG_PAIRS[5], SEG_PAIRS[6], SEG_PAIRS[2], SEG_PAIRS[3] } },
    { 6, { SEG_PAIRS[0], SEG_PAIRS[5], SEG_PAIRS[6], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[4] } },
    { 7, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2] } },
    { 8, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[4], SEG_PAIRS[5], SEG_PAIRS[6] } },
    { 9, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[5], SEG_PAIRS[6] } }
};