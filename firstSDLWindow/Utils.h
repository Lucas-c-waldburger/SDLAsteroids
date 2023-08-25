#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>


const int SCREEN_WIDTH = 1344, SCREEN_HEIGHT = 756;

namespace Utils
{

    struct LDPoint : public SDL_Point
    {
        LDPoint() : SDL_Point() {};
        LDPoint(int xPos, int yPos) : SDL_Point() { x = xPos; y = yPos; };
        LDPoint(const LDPoint& other) { x = other.x; y = other.y; };

        LDPoint& operator=(const LDPoint& other) { if (*this != other) { this->x = other.x; this->y = other.y; } return *this; }

        bool operator==(const LDPoint& other) const { return this->x == other.x && this->y == other.y; }
        bool operator!=(const LDPoint& other) const { return this->x != other.x || this->y != other.y; }

        bool operator<(const LDPoint& other) const { return this->x < other.x && this->y < other.y; }
        bool operator>(const LDPoint& other) const { return this->x > other.x && this->y > other.y; }
        bool operator>=(const LDPoint& other) const { return this->x >= other.x && this->y >= other.y; }

        LDPoint operator+(int i) { return LDPoint{ this->x + i, this->y + i }; }
        LDPoint operator-(int i) { return LDPoint{ this->x - i, this->y - i }; }
        LDPoint operator-(LDPoint& other) { return LDPoint{ this->x - other.x, this->y - other.y }; }

        void operator+=(LDPoint& other) { this->x += other.x; this->y += other.y; }
        void operator+=(int i) { this->x += i; this->y += i; }

        friend std::ostream& operator<<(std::ostream& stream, LDPoint& p) { stream << p.x << ", " << p.y; return stream; };

    };

    template <typename LDPoint>
    void logPoints(typename std::vector<LDPoint>::iterator it1, typename std::vector<LDPoint>::iterator it2)
    {
        for (; it1 != it2; it1++)
            SDL_Log("(%i, %i)", it1->x, it1->y);
    }

    struct LinePoints
    {

        static LDPoint extendLine(const LDPoint& A, const LDPoint& B, int distance)
        {
            LDPoint C;

            double lenAB = sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));

            C.x = A.x + (distance * (B.x - A.x) / lenAB);
            C.y = A.y + (distance * (B.y - A.y) / lenAB);

            return C;
        }


        static bool pointWithinScreenBounds(const LDPoint& p, int screenWidthMin = 0, int screenWidthMax = SCREEN_WIDTH, int screenHeightMin = 0, int screenHeightMax = SCREEN_HEIGHT)
        {
            return ((p.x >= screenWidthMin && p.x <= screenWidthMax) &&
                (p.y >= screenHeightMin && p.y <= screenHeightMax));
        }


        static void generateLinePointsToEdge(const LDPoint& A, const LDPoint& B, std::vector<LDPoint>& pathPoints, int distanceBetweenPixels = 2)
        {
            int i = 0;
            LDPoint projectedPoint = extendLine(A, B, i);
            while (pointWithinScreenBounds(projectedPoint))
            {
                pathPoints.push_back(projectedPoint);
                i += distanceBetweenPixels;
                projectedPoint = extendLine(A, B, i);
            }
        }
    };


};

























