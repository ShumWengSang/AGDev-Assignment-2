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

	 void SetPosition(CVector3 theNewPosition);
	 void SetScale(CVector3 theNewScale, bool LeftUp);
	 CVector3 theScale;

	 CVector3 GetScale();

	 CVector3 GetTopLeft()
	 {
		 CVector3 TopLeft;
		 MinMax ObjX = GetMinMax(theObjectX.theObj_LowPoly);
		 float ObjWidthX = ObjX.MaxX - ObjX.MinX ;
		 TopLeft.x = ObjX.MinX + ObjWidthX / 2 * theScale.x + theObjectX.GetPosition().x;
		 MinMax ObjZ = GetMinMax(theObjectZ.theObj_LowPoly);
		 float ObjLengthZ = ObjZ.MaxZ - ObjX.MinZ;
		 TopLeft.z = ObjZ.MaxZ + ObjLengthZ / 2 * theScale.y + theObjectZ.GetPosition().z;
		 return TopLeft;
	 }
	 CVector3 GetBottomRight()
	 {
		 CVector3 BottomRight;
		 MinMax ObjX = GetMinMax(theObjectX.theObj_LowPoly);
		 float ObjWidthX = ObjX.MaxX - ObjX.MinX;
		 BottomRight.x = ObjX.MaxX + ObjWidthX / 2 * theScale.x + theObjectX.GetPosition().x;
		 MinMax ObjZ = GetMinMax(theObjectZ.theObj_LowPoly);
		 float ObjLengthZ = ObjZ.MaxZ - ObjX.MinZ;
		 BottomRight.z = ObjZ.MinZ + ObjLengthZ / 2 * theScale.y + theObjectZ.GetPosition().z;
		 return BottomRight;
	 }
};

