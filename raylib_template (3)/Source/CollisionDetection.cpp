#include "CollisionResources.h"
#include "raylib.h"
#include <math.h>

bool CollisionDetection::CircleCircle(Vector2 circle1Pos, float circle1Radius, Vector2 circle2Pos, float circle2Radius)
{
	return
		((circle1Pos.x - circle2Pos.x) * (circle1Pos.x - circle2Pos.x) +
		(circle1Pos.y - circle2Pos.y) * (circle1Pos.y - circle2Pos.y) < 
		(circle1Radius + circle2Radius) * (circle1Radius + circle2Radius));
}

bool CollisionDetection::CircleBoundingBox(Vector2 circlePos, float circleRadius, Vector2 boxPos, Vector2 boxSize)
{
	Vector2 point = circlePos;

	if (circlePos.x < boxPos.x) 
	{ 
		point.x = boxPos.x; 
	}
	else if (circlePos.x > boxPos.x + boxSize.x) 
	{ 
		point.x = boxPos.x + boxSize.x; 
	}

	if (circlePos.y < boxPos.y) 
	{ 
		point.y = boxPos.y; 
	}
	else if (circlePos.y > boxPos.y + boxSize.y) 
	{ 
		point.y = boxPos.y + boxSize.y; 
	}

	float distX = circlePos.x - point.x;
	float distY = circlePos.y - point.y;
	float distanceSquared = (distX * distX) + (distY * distY);

	if (distanceSquared <= circleRadius * circleRadius) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool CollisionDetection::BoundingBoxBoundingBox(Vector2 box1Pos, Vector2 box1Size, Vector2 box2Pos, Vector2 box2Size)
{
	if (box1Pos.x < box2Pos.x + box2Size.x &&
		box1Pos.x + box1Size.x > box2Pos.x &&
		box1Pos.y < box2Pos.y + box2Size.y &&
		box1Pos.y + box1Size.y > box2Pos.y) {

		return true;
	}
	else 
	{
		return false;
	}
}
 
bool CollisionDetection::CircleLineSegment(Vector2 circlePos, float circleRadius, Vector2 LinePos1, Vector2 LinePos2)
{
	float lineVectorX = LinePos2.x - LinePos1.x;
	float lineVectorY = LinePos2.y - LinePos1.y;
	float circleLineVectorX = circlePos.x - LinePos1.x;
	float circleLineVectorY = circlePos.y - LinePos1.y;
	float dotProduct = circleLineVectorX * lineVectorX + circleLineVectorY * lineVectorY;
	float lengthSquared = lineVectorX * lineVectorX + lineVectorY * lineVectorY;
	float t = dotProduct / lengthSquared;
	if (t > 1)
	{
		t = 1;
	}
	else if (t < 0)
	{
		t = 0;
	}
	float closestX = LinePos1.x + t * lineVectorX;
	float closestY = LinePos1.y + t * lineVectorY;
	float distance = (float)sqrt(pow((double)(closestX - circlePos.x), 2.0) + pow((double)(closestY - circlePos.y), 2.0));
	return distance <= circleRadius;
}