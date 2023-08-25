#pragma once

#include "Asteroid.h"
#include <algorithm>

class ObjectDestructionManager
{
public:
    ObjectDestructionManager() = default;
    void resolveAll(Ship& ship, AsteroidGenerator& asteroidGenerator);

private:
    template <class T>
    void eraseMarked(std::vector<T>& objVec);
    bool collided(Bullet& bullet, Asteroid& asteroid);

    template <class T>
    int checkExpiration(std::vector<T>& objVec);

    bool checkShipCollision(Ship& ship, AsteroidGenerator& asteroidGenerator);
    int checkBulletCollisions(BulletGenerator& bulletGenerator, AsteroidGenerator& asteroidGenerator);

    void resolveExpirations(BulletGenerator& bulletGenerator, AsteroidGenerator& asteroidGenerator);
    void resolveBulletCollisions(BulletGenerator& bulletGenerator, AsteroidGenerator& asteroidGenerator);
};

