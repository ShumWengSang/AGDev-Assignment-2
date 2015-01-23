#include "FrustumGEO.h"

CFrustumG::CFrustumG(void)
{
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	angle = 0;

	farDist = 50.f;
	nearDist = 1.f;

	fPosition = CVector3(0,0,-5);
	fDirection = CVector3(0,0,3.14159f);
	fUp = CVector3(0,1,0);
}

CFrustumG::~CFrustumG(void)
{
}

void CFrustumG::Update( CVector3 newPos,CVector3 newDir)
{

	fPosition = newPos;
	fDirection = newDir;

	Update();
}

// Update the frustum
void CFrustumG::Update()
{

	heightNear = 2 * tan(FOVY*0.5f) * nearDist;
	heightFar  = 2 * tan(FOVY*0.5f) * farDist;

	widthNear = heightNear* ASPECT_RATIO;
	widthFar  = heightFar * ASPECT_RATIO;

	farC = fPosition + (fDirection.NormalizedVector3D() * farDist);
	nearC = fPosition + (fDirection.NormalizedVector3D() * nearDist);

	right = CVector3::Cross((fDirection.NormalizedVector3D()),( up ));

	ftl = farC + up * (heightFar*0.5f) - right * (widthFar * 0.5f);
	ftr = farC + up * (heightFar*0.5f) + right * (widthFar * 0.5f);
	fbl = farC - up * (heightFar*0.5f) - right * (widthFar * 0.5f);
	fbr = farC - up * (heightFar*0.5f) + right * (widthFar * 0.5f);

	ntl = nearC + up * (heightNear*0.5f) - right * (widthNear * 0.5f);
	ntr = nearC + up * (heightNear*0.5f) + right * (widthNear * 0.5f);
	nbl = nearC - up * (heightNear*0.5f) - right * (widthNear * 0.5f);
	nbr = nearC - up * (heightNear*0.5f) + right * (widthNear * 0.5f);

	CVector3 vector1,vector2;

	//updating farplane Vector
	vector1 = fbl - ftl;
	vector2 = ftr - ftl;
	farV = CVector3::Cross(vector1, vector2 );
	farV = farV.NormalizedVector3D();
	

	//updating nearplane Vector
	vector1 = nbl - ntl;
	vector2 = ntr - ntl;
	nearV = CVector3::Cross(vector1, vector2 );
	nearV = nearV.NormalizedVector3D();

	//updating btmplane Vector
	vector1 = nbl - fbl;
	vector2 = fbr - fbl;
	btmV = CVector3::Cross(vector1, vector2 );
	btmV = btmV.NormalizedVector3D();

	//updating topplane Vector
	vector1 = ntl - ftl;
	vector2 = ftr - ftl;
	topV = CVector3::Cross(vector1, vector2 );
	topV = topV.NormalizedVector3D();

	//updating leftPlane Vector
	vector1 = nbl - ntl;
	vector2 = ftl - ntl;
	leftV = CVector3::Cross(vector1, vector2 );
	leftV = leftV.NormalizedVector3D();

	//updating rightPlaneVector
	vector1 = ftr - ntr;
	vector2 = nbr - ntr;
	rightV = CVector3::Cross(vector1, vector2 );
	rightV = rightV.NormalizedVector3D();
}

// Draw the frustum
void CFrustumG::Draw(void)
{
//	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
		glColor4f( 0.0f, 0.0f, 1.0f, 0.3f);
		glBegin( GL_QUADS );
			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(ntl.x, ntl.y, ntl.z);

			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);
			
			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);
			
			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(nbl.x, nbl.y, nbl.z);

			
			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(ntr.x, ntr.y, ntr.z);

			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);
			
			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);
			
			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(nbr.x, nbr.y, nbr.z);


			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);

			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);

			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);

			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);

			
			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ntr.x, ntr.y, ntr.z);
			
			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);
			
			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);
			
			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(ntl.x, ntl.y, ntl.z);

			
			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(nbr.x, nbr.y, nbr.z);
			
			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);
			
			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);
			
			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(nbl.x, nbl.y, nbl.z);
			
		glEnd();
		glDisable( GL_BLEND );
	glPopAttrib();

		// Draw the lines of the Frustum
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(10);
		glBegin( GL_LINES );
			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ntr.x, ntr.y, ntr.z);

			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(nbr.x, nbr.y, nbr.z);

			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(nbl.x, nbl.y, nbl.z);

			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(ntl.x, ntl.y, ntl.z);

			
			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);

			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);

			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);

			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);


			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);
			
			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);

			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);

			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);
		glEnd();
		glLineWidth(1);
//	glPopMatrix();
}

// Perform containment check for a position with respect to the Frustum
bool CFrustumG::ContainmentCheck( CVector3 position)
{
	CVector3 pointToPos;
	float angle;

	//checking against far plane
	pointToPos = position - ftl;
	angle = CVector3::DotProduct((pointToPos.NormalizedVector3D()), farV );
	
	if (angle < 0)
	{
		return false;
	}

	//checking against near plane
	pointToPos = position - ntl;
	angle = CVector3::DotProduct((pointToPos.NormalizedVector3D()), nearV );

	if (angle > 0)
	{
		return false;
	}

	//checking against btm plane
	pointToPos = position - fbl;
	angle = CVector3::DotProduct((pointToPos.NormalizedVector3D()), btmV );

	if (angle < 0)
	{
		return false;
	}

	//checking against top plane
	pointToPos = position - ftl;
	angle = CVector3::DotProduct((pointToPos.NormalizedVector3D()), topV );

	if (angle > 0)
	{
		return false;
	}

	//checking against left plane
	pointToPos = position - ntl;
	angle = CVector3::DotProduct((pointToPos.NormalizedVector3D()), leftV );

	if (angle < 0)
	{
		return false;
	}
	
	//checking against right plane
	pointToPos = position - ntr;
	angle = CVector3::DotProduct((pointToPos.NormalizedVector3D()), rightV );

	if (angle < 0)
	{
		return false;
	}
	return true;
}

int CFrustumG::ContainmentCheckSpheres(CVector3 position, float radius)
{
#define INSIDE 0
#define OUTSIDE 1
#define INTERSECT 3

	float distance;
	int result = INSIDE;

	for (int i = 0; i < 6; i++) {
		//distance = pl[i].distance(p);
		if (distance < -radius)
			return OUTSIDE;
		else if (distance < radius)
			result = INTERSECT;
	}
	return(result);

}