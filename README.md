# SDL Asteroids

![SDL_Asteroids footage](sdl_asteroids_gameplay_1.gif?raw=true "SDL_Asteroids_footage")


Each game object is a vector of points representing a circle. The top of the inheritance tree (class CircleDraw) utilizes Bresenhan's algorithm 
to approximate the perimeter points - sequentially determining the Y-axis change of each point within the first octant (yChangeDecision) and reflecting the points around the circle.

```
void CircleDraw::findPerimeterPoints()
{
    ...
    
    int yChangeDecision = 3 - (2 * radius);
    
    while (perimeterPoints.back().x < perimeterPoints.back().y)
        yChangeDecision = decideNext(yChangeDecision, perimeterPoints.back());
}
```
```
int CircleDraw::decideNext(int prevYChangeDecision, LDPoint prevPoint)
{
    ...
    
    if (prevYChangeDecision < 0)
    {
        nextPoint = LDPoint{ prevPoint.x + 1, prevPoint.y };
        newYChangeDecision = prevYChangeDecision + 4 * prevPoint.x + 6;
    }
    else
    {
        nextPoint = LDPoint{ prevPoint.x + 1, prevPoint.y - 1 };
        newYChangeDecision = prevYChangeDecision + 4 * (prevPoint.x - prevPoint.y) + 10;
    }

    reflectAndStore(LDPoint{ nextPoint.y, nextPoint.x }); reflectAndStore(nextPoint);
    return newYChangeDecision;
}
```

Object movement is handled by populating another vector of path points through a line-approximation algorithm. The path is projected in its
entirety (either forward or bi-directionally) and not recalculated unless the object is rotated.

```
std::vector<LDPoint> PathPoints::makeSinglePath(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistanceBetweenPoints)
{
    ...

    while (LinePoints::pointWithinScreenBounds(projectedPoint)) 
    {
        singlePath.push_back(projectedPoint);
        i += pixelDistanceBetweenPoints;
        projectedPoint = LinePoints::extendLine(v1, v2, i);
    }
    return singlePath;
}
```
```
std::vector<LDPoint> PathPoints::makeBiDirectionalPath(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistanceBetweenPoints)
{
    std::vector<LDPoint> biDirectionalPath = makeSinglePath(v1, v2, 0, pixelDistanceBetweenPoints);
    std::vector<LDPoint> backwardPath = makeSinglePath(v2, v1, startingDistanceFromV1, pixelDistanceBetweenPoints);

    biDirectionalPath.insert(biDirectionalPath.end(), backwardPath.rbegin(), backwardPath.rend());
    return biDirectionalPath;
}
```

Creating different n-sided shapes and rotating them is accomplished through subdividing the base circle's perimeter points into n-equal parts, keeping track of their relative position through a dynamic vector of indices, and rendering lines between them.

```
void CInscribedShape::init() // Derived from CircleDraw
{
    ...
    
    vertexPoints.reserve(numVertices + 1);
    assignVertexIndexes();
    updateVertexPoints();
}
```

Other features include
- Score display
- Particle effects for the background star decorations
- Ship leaving and entering the screen through the correct projected vector
- Approximation of velocity for ship movement
- Scaling difficulty

Recommended Setup
- Just clone the repo and open the .sln in visual studio

![SDL_Asteroids footage2](sdl_asteroids_gameplay_2.gif?raw=true "SDL_Asteroids_footage2")
