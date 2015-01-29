#pragma once
#include "Vector3.h"
#include "BaseEntity.h"
#include "tgaLoader.h"

//struct MinMax;

class BlockWall : public BaseEntity
{
public:
	BlockWall();
	~BlockWall();

	 bool glRenderObject(CVector3* theCameraPosition);
	 bool glRenderObject(int RESOLUTION);

	 EntityType getObjectType(void);


	 CVector3 getPosition(void);


	 CVector3 getDirection();


	 CObjectModel GetObjectModel()
	 {
		 CObjectModel theObject;
		 return  theObject;
	 }
	 CObjectModel theObjectX;
	 CObjectModel theObjectZ;
	 Matrix4x4 Scalef;

	 void SetPosition(CVector3 theNewPosition);
	 void SetScale(CVector3 theNewScale, bool LeftUp);
	 CVector3 theScale;

	 CVector3 GetScale();

	 CVector3 GetTopLeft()
	 {
		 float resultant;
		 glGetFloatv(GL_MATRIX_MODE, &resultant);
		 MinMax ObjX = GetMinMax(theObjectX.theObj_LowPoly);
		 MinMax ObjZ = GetMinMax(theObjectZ.theObj_LowPoly);

		 CVector3 TopLeft(ObjX.MinX, 0, ObjZ.MaxZ );
		 TopLeft = TopLeft * Scalef;
		 TopLeft = TopLeft + CVector3(theObjectX.GetPosition().x, 0, theObjectZ.GetPosition().z);

		// CVector3 result = TopLeft * Scalef;
		 return TopLeft;
	 }
	 CVector3 GetBottomRight()
	 {

		 MinMax ObjX = GetMinMax(theObjectX.theObj_LowPoly);
		 MinMax ObjZ = GetMinMax(theObjectZ.theObj_LowPoly);

		 CVector3 BottomRight(ObjX.MaxX, 0, ObjZ.MinZ);
		 BottomRight = BottomRight * Scalef;
		 BottomRight = BottomRight + CVector3(theObjectX.GetPosition().x + theObjectX.TOffset.x, 0, theObjectZ.GetPosition().z + theObjectZ.TOffset.z);

		 return BottomRight;

	 }
};

