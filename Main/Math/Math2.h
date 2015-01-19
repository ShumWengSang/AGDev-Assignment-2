#pragma once

#include "Vector3.h" 
#include <math.h>
class Math
{
public:

	public:
	static	const float PI2;
	static	const float HALF_PI;
	static	const float EPSILON;

	static bool closeEnough(float f1, float f2)
	{
		// Determines whether the two floating-point values f1 and f2 are
		// close enough together that they can be considered equal.

		return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	}

	static float degreesToRadians(float degrees)
	{
		return (degrees * PI2) / 180.0f;
	}

	static float radiansToDegrees(float radians)
	{
		return (radians * 180.0f) / PI2;
	}


	static float VectorToAngle(CVector3 vector)
	{
		return atan2(vector.y, vector.x);
	}
};

