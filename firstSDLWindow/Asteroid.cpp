#include "Asteroid.h"


Asteroid::Asteroid(SDL_Renderer*& renderer, int r, LDPoint c, int numVerts) : CInscribedShape(renderer, r, c, numVerts), pathIndex(1), markedDestroy(false)
{
    do
    {
        path.clear();
        LinePoints::generateLinePointsToEdge(center, randomizeStartingPerimeterPoint(), path, 1);
    } 
    while (path.size() < MINIMUM_PATH_LENGTH);
}


LDPoint Asteroid::randomizeStartingPerimeterPoint()
{
    // selects a random perimeter point to begin building a forward path from 
    int randIndex = rand() % perimeterPoints.size();
    LDPoint randomizedPerimeterPointForMoveDirection = perimeterPoints[randIndex];

    // re-rolls starting path until path is gauranteed to take it through the visible screen 
    while (!LinePoints::pointWithinScreenBounds(randomizedPerimeterPointForMoveDirection))
    {
        randIndex = rand() % perimeterPoints.size();
        randomizedPerimeterPointForMoveDirection = perimeterPoints[randIndex];
    }

    return randomizedPerimeterPointForMoveDirection;
}


void Asteroid::moveForward(int speed)
{
    LDPoint& nextPoint = path[pathIndex];
    move(nextPoint - center);
    
    rotate(numVertices % 2 == 0 ? 1 : -1);
    pathIndex += speed;
}


// ASTEROID GENERATOR //
AsteroidGenerator::AsteroidGenerator(SDL_Renderer* renderer) : pRenderer(renderer), asteroidRadius(MIN_ASTEROID_RADIUS), asteroidNumVertices(STARTING_NUM_VERTICIES),
asteroidSpeed(STARTING_ASTEROID_SPEED), waitBetweenSpawn(STARTING_WAIT_BETWEEN_ASTEROID_SPAWN), maxAsteroidsOnScreen(STARTING_MAX_ASTEROIDS_ON_SCREEN), numDestroyed(0)
{}


AsteroidGenerator::~AsteroidGenerator()
{
    pRenderer = nullptr;
}


LDPoint AsteroidGenerator::randomizeCenter()
{
    LDPoint center{ 0, 0 };
    int alongX = 0;

    auto randXBound = []() { return (rand() % 2 == 0) ? 0 : SCREEN_WIDTH; };
    auto randYBound = []() { return (rand() % 2 == 0) ? 0 : SCREEN_HEIGHT; };
    auto randXPoint = []() { return (rand() % (SCREEN_WIDTH + 1)); };
    auto randYPoint = []() { return (rand() % (SCREEN_HEIGHT + 1)); };

    int xOrYStart = rand() % 2;

    if (xOrYStart == alongX)
    {
        center.x = randXBound();
        center.y = randYPoint();    }
    else
    {
        center.x = randXPoint();
        center.y = randYBound();
    }

    return center;
}


int AsteroidGenerator::randomizeRadius()
{
    return MIN_ASTEROID_RADIUS + (rand() % (MAX_ASTEROID_RADIUS_ADDITION + 1));
}


void AsteroidGenerator::makeAsteroid()
{
    asteroids.emplace_back(pRenderer, randomizeRadius(), randomizeCenter(), asteroidNumVertices);
}


void AsteroidGenerator::drawAll()
{
    handleSpawn();

    for (auto it = asteroids.begin(); it != asteroids.end(); it++)
    {
        it->moveForward(asteroidSpeed);
        it->draw();
    }
}


void AsteroidGenerator::handleSpawn()
{
    if (spawnTime.waitOver() && asteroids.size() < maxAsteroidsOnScreen)
    {
        makeAsteroid();
        spawnTime.setWait(waitBetweenSpawn);
    }
}


const int AsteroidGenerator::getSpeed()
{
    return asteroidSpeed;
}


void AsteroidGenerator::setSpeed(int newSpeed)
{
    asteroidSpeed = newSpeed;
}


const int AsteroidGenerator::getNumDestroyed()
{
    return numDestroyed;
}


void AsteroidGenerator::addToNumDestroyed(int amount)
{
    numDestroyed += amount;
}


const int AsteroidGenerator::getWaitBetweenSpawn()
{
    return waitBetweenSpawn;
}


void AsteroidGenerator::setWaitBetweenSpawn(int amount)
{
    waitBetweenSpawn = amount;
}


const int AsteroidGenerator::getMaxAsteroids()
{
    return maxAsteroidsOnScreen;
}


void AsteroidGenerator::setMaxAsteroids(int amount)
{
    maxAsteroidsOnScreen = amount;
}

