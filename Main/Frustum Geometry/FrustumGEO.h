#pragma once
#include <windows.h> // Header File For Windows_

#include <gl\gl.h> // Header File For The OpenGL32 Library

#include <gl\glu.h> // Header File For The GLu32 Library

#include "Vector3.h"
#include <math.h>



#define FOVY 45
#define ASPECT_RATIO 1.33f

class CFrustumG
{
private:
	GLfloat angle, farDist, nearDist, heightNear, heightFar, widthNear, widthFar;

	CVector3 farC,nearC;
	CVector3 fPosition, fDirection, fUp;
	CVector3 up, right;

	CVector3 ftl,ftr,fbl,fbr;
	CVector3 ntl,ntr,nbl,nbr;
	CVector3 farV,nearV,leftV,rightV,topV,btmV;

public:
	CFrustumG(void);
	~CFrustumG(void);
	// Update the frustum
	void Update();
	// Draw the frustum
	void Update(CVector3 newPos, CVector3  newDir);
	// Draw the frustum
	void Draw(void);
	// Perform containment check for a position with respect to the Frustum
	bool ContainmentCheck( CVector3 position);
	int ContainmentCheckSpheres(CVector3 position, float radius);
};