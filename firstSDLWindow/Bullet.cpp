#include "Bullet.h"

Bullet::Bullet(std::vector<LDPoint> currentBulletPathProjection) : path(currentBulletPathProjection), pathIndex(0), markedDestroy(false)
{
    updateRectXY();
    w = BULLET_WIDTH;
    h = BULLET_HEIGHT;
}

void Bullet::updateRectXY()
{
    x = path[pathIndex].x;
    y = path[pathIndex].y;
}


BulletGenerator::BulletGenerator(SDL_Renderer*& pRenderer) : pRendererRef(pRenderer), time({})
{}


void BulletGenerator::makeBullet(std::vector<LDPoint> currentBulletPathProjection)
{
    if (currentBulletPathProjection.size() > 0)
    {
        bullets.emplace_back(currentBulletPathProjection);
        time.setWait(WAIT_BETWEEN_BULLET);
    }
}


void BulletGenerator::drawAll()
{
    if (!bullets.empty())
    {
        SDL_SetRenderDrawColor(pRendererRef, 255, 0, 0, 255);

        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            it->pathIndex = (it->pathIndex + BULLET_SPEED < it->path.size()) ? 
                it->pathIndex + BULLET_SPEED : it->path.size() - 1;
            it->updateRectXY();
            SDL_RenderFillRect(pRendererRef, &(*it));
        }
    }
}
