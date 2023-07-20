#include "Bullet.h"



Bullet::Bullet(std::vector<LDPoint> currentForwardPathProjection) : forwardPathProjection(currentForwardPathProjection), pathIndex(0), active(true)
{
	x = forwardPathProjection[0].x;
	y = forwardPathProjection[0].y;
	w = BULLET_WIDTH;
	h = BULLET_HEIGHT;

}

void Bullet::updateRectXY()
{
	x = forwardPathProjection[pathIndex].x;
	y = forwardPathProjection[pathIndex].y;
}




BulletGenerator::BulletGenerator(SDL_Renderer*& pRenderer) : pRendererRef(pRenderer)
{}
 

void BulletGenerator::makeBullet(std::vector<LDPoint> currentForwardPathProjection)
{
	//auto inactiveBullet = std::find(bullets.begin(), bullets.end(), [](Bullet& bullet) { return !bullet.active; });

	//if (inactiveBullet != bullets.end())
	//{
	//	inactiveBullet->forwardPathProjection = currentForwardPathProjection;
	//	inactiveBullet->pathIndex = 0;
	//	inactiveBullet->active = true;
	//}

	//else
		bullets.emplace_back(currentForwardPathProjection);
}

void BulletGenerator::drawAll()
{
	//for (auto& bullet : bullets)
	//{
	//	if ()
	//}

	

	for (auto it = bullets.begin(); it != bullets.end();)
	{

		if (it->pathIndex >= it->forwardPathProjection.size() - 1) 
			it = bullets.erase(it);

		else
		{
			it->pathIndex++;
			it->updateRectXY();
			++it;
		}
	}
	
	if (!bullets.empty())
	{
		SDL_SetRenderDrawColor(pRendererRef, 255, 0, 0, 255);
		SDL_RenderFillRects(pRendererRef, &bullets[0], bullets.size());
	}
}
