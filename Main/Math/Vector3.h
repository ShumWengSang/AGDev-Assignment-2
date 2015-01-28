#pragma once
#include <math.h>
#include "Matrix4x4.h"
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

	bool operator== (const CVector3& rhs) const;

	void Set(float X, float Y, float Z);
	void Set(CVector3);

	float GetMagnitude();

	static CVector3 CVector3::Cross(CVector3 vVector1, CVector3 vVector2);
	static float DotProduct(CVector3 vVector1, CVector3 vVector2);
	CVector3 Normalize(CVector3 vNormal);

	CVector3 operator*(const Matrix4x4 &m) const
	{
		return CVector3(x*m.matrix[0] + y*m.matrix[4] + z*m.matrix[8] + 1 * m.matrix[12],
			x*m.matrix[1] + y*m.matrix[5] + z*m.matrix[9] + 1 * m.matrix[13],
			x*m.matrix[2] + y*m.matrix[6] + z*m.matrix[10] + 1 * m.matrix[14]);
	}

	float x, y, z;
};


