#pragma once
#include <cmath>
class CVector3
{
public:

	// A default constructor
	CVector3() {}

	// This is our constructor that allows us to initialize our data upon creating an instance
	CVector3(float X, float Y, float Z);


	// Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 vVector);


	// Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 vVector);


	// Here we overload the * operator so we can multiply by scalars
	CVector3 operator*(float num);


	// Here we overload the / operator so we can divide by a scalar
	CVector3 operator/(float num);


	CVector3 NormalizedVector3D();




	float x, y, z;
};


