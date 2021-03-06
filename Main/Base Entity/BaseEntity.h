#pragma once
#include "Vector3.h"
#include "ObjectModel.h"
enum EntityType
{
	NONE = 0,
	PLAYER = 1,
	HorizontalWall,
	ENEMY,
	EXIT
};

class BaseEntity
{
public:
	EntityType theType;
	BaseEntity();
	BaseEntity(const BaseEntity& o);
	virtual ~BaseEntity();

	virtual bool glRenderObject(CVector3 theCameraPosition);
	virtual bool glRenderObject(int RESOLUTION);
	// Designed to render the specified object.  Returns TRUE if the object is successfully
	// rendered, otherwise FALSE.  All derived objects are expected to override this
	// function.

	virtual EntityType getObjectType(void);
	// Returns the type of the object.  The return type needs to be one of the enumerated
	// BaseEntity_Type types listed above.  All derived classes are expected to override this
	// function.

	virtual CVector3 getPosition(void);
	// Returns the center position of the object.  This is used to obtain an idea of where
	// the object is located within a graphical scene.  Returns a myVector, not a pointer so
	// the position can be manipulated without effecting the object.  All derived classes are 
	// expected to override this function.
	virtual CVector3 getDirection();

	virtual bool operator== (BaseEntity& o);
	// Operator overloaded equivalence.  Determines whether or no two objects are identical.
	// All derived classes are expected to override this function if a getter detail of 
	// examination is required.

	virtual CObjectModel GetObjectModel();

	virtual CVector3 GetScale();
	virtual CVector3 GetTopLeft()
	{
		return CVector3(0, 0, 0);
	}
	virtual CVector3 GetBottomRight()
	{
		return CVector3(0, 0, 0);
	}

private:
};

//Note: 
/*
There seems to be a problem with the linkage of this file. Sometimes it cannot include the CVector3 file.
*/