#include "Vector3.h"

// This computes the magnitude of a normal.   (magnitude = sqrt(x^2 + y^2 + z^2)
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

// This returns the cross product between 2 vectors
CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vCross;								// The vector to hold the cross product
	// Get the X value
	vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	// Get the Y value
	vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	// Get the Z value
	vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vCross;								// Return the cross product
}

// This returns the normal of a vector
CVector3 Normalize(CVector3 vNormal)
{
	double Magnitude;							// This holds the magitude			

	Magnitude = Mag(vNormal);					// Get the magnitude

	vNormal.x /= (float)Magnitude;				// Divide the vector's X by the magnitude
	vNormal.y /= (float)Magnitude;				// Divide the vector's Y by the magnitude
	vNormal.z /= (float)Magnitude;				// Divide the vector's Z by the magnitude

	return vNormal;								// Return the normal
}

CVector3::CVector3(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
}

// Here we overload the + operator so we can add vectors together 
CVector3 CVector3::operator+(CVector3 vVector)
{
	// Return the added vectors result.
	return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
}

// Here we overload the - operator so we can subtract vectors 
CVector3 CVector3::operator-(CVector3 vVector)
{
	// Return the subtracted vectors result
	return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
}

// Here we overload the * operator so we can multiply by scalars
CVector3 CVector3::operator*(float num)
{
	// Return the scaled vector
	return CVector3(x * num, y * num, z * num);
}

// Here we overload the / operator so we can divide by a scalar
CVector3 CVector3::operator/(float num)
{
	// Return the scale vector
	return CVector3(x / num, y / num, z / num);
}

CVector3 CVector3::NormalizedVector3D()
{
	float magnitude = sqrtf(x * x + y * y + z * z);
	float X = x / magnitude;
	float Y = y / magnitude;
	float Z = z / magnitude;
	return CVector3(X, Y, Z);
}

bool CVector3::operator== (const CVector3& rhs) const
{
	if (this->x == rhs.x)
	{
		if (this->y == rhs.y)
		{
			if (this->z == rhs.z)
			{
				return true;
			}
		}
	}

	return false;
}

void CVector3::Set(float X, float Y, float Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}

float CVector3::GetMagnitude()
{
	return sqrtf(x * x + y * y + z * z);
}