#include "Ship.h"

Ship::Ship(SDL_Renderer* renderer, int r, LDPoint c) :
    CInscribedShape(renderer, r, c, 3),
    bulletGenerator(BulletGenerator{ rendererCpy }), path(center, getHead(), radius, 1, false),
    currentPathIndex(1), markedDestroy(false), markedRecalculatePath(false),
    velocityTime(MAX_DELAY, MIN_DELAY, BASE_DELAY_CHANGE_AMOUNT)
{}


void Ship::draw()
{
    CInscribedShape::draw();
    //    SDL_RenderDrawPoints(rendererCpy, &path[0], path.size());
}

void Ship::rotate(int amount)
{
    CInscribedShape::rotate(amount);
    markedRecalculatePath = true;
}

void Ship::goForward()
{


    //    std::cout << "CURRENTPATHINDEX: " << currentPathIndex << '\n';
    LDPoint nextPoint = path[currentPathIndex];
    move(nextPoint - center);

    int modValue = (path.size() - 1 > 0) ? path.size() - 1 : 1;
    currentPathIndex = (currentPathIndex + SHIP_INDEX_MOVE_PER_FRAME) % modValue;
}


LDPoint Ship::getHead()
{
    return perimeterPoints[vertexIndecies[0]];
}


void Ship::updateShipPath()
{
    path.path = PathPoints::makeBiDirectionalPath(center, getHead(), radius, 1);
    currentPathIndex = 1;
}


void Ship::handleKeyStates(const Uint8*& keystates)
{
    if (keystates[SDL_SCANCODE_A])
        rotate(2);

    else if (keystates[SDL_SCANCODE_D])
        rotate(-2);

    if (keystates[SDL_SCANCODE_W])
    {
        if (velocityTime.decideMovement(true))
        {
            if (markedRecalculatePath)
            {
                updateShipPath();
                markedRecalculatePath = false;
            }
            goForward();
        }
    }

    else
    {
        if (velocityTime.decideMovement(false) && velocityTime.currentDelay < velocityTime.maxDelay)
        {
            goForward();
        }
    }

    if (keystates[SDL_SCANCODE_SPACE])
    {
        if (bulletGenerator.time.waitOver())
        {
            std::vector<LDPoint> pathFromCenter = PathPoints::makeSinglePath(center, getHead(), 0, 2);
            bulletGenerator.makeBullet(PathPoints::clipFrom(pathFromCenter, getHead(), 1));
        }
    }
}