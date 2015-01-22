#pragma once
#include <windows.h>
#include <mmsystem.h>

#include <gl\GL.h>
#include <gl\GLU.h>
#include "Mouse.h"
#include "Vector3.h"
enum CameraType {
  FirstPerson = 1,
  ThirdPerson = 2
};


// This is our camera class
class CCamera {

public:

	// Our camera constructor
	CCamera();
	CCamera(CameraType theType);
	~CCamera();

	// These are are data access functions for our camera's private data
	inline CVector3 Position() {	return m_vPosition;		}
	inline CVector3 View()		{	return m_vView;			}
	inline CVector3 UpVector() { return m_vUpVector; }
	inline CVector3 Strafe()	{ return m_vStrafe; }
	
	// This changes the position, view, and up vector of the camera.
	// This is primarily used for initialization
	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);

	// This rotates the camera's view around the position depending on the values passed in.
	void RotateView(float angle, float X, float Y, float Z);

	// This moves the camera's view by the mouse movements (First person view)
	void SetViewByMouse();

	void SetViewByMouseTwo(float x,float y);

	// This rotates the camera around a point (I.E. your character).
	void RotateAroundPoint(CVector3 vCenter, float angle, float X, float Y, float Z);

	// This strafes the camera left or right depending on the speed (+/-) 
	void StrafeCamera(float speed);

	// This will move the camera forward or backward depending on the speed
	void MoveCamera(float speed);

	// This checks for keyboard movement
	void CheckForMovement();

	// This updates the camera's view and other data (Should be called each frame)
	void Update();

	// This uses gluLookAt() to tell OpenGL where to look
	void Look();

	void SetDT(float);
	void SetHeightWidth(int, int);


private:
	CameraType theType;

	// The camera's position
	CVector3 m_vPosition;					

	// The camera's view
	CVector3 m_vView;						

	// The camera's up vector
	CVector3 m_vUpVector;		
	
	// The camera's strafe vector
	CVector3 m_vStrafe;	

	float g_DT;		
	int SCREENHEIGHT;
	int SCREENWIDTH;

	CMouse theMouse;

	void calculations(float diffX, float diffY);
	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	float Angle;
};



/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// Nothing was added to this file since the Camera5 tutorial on strafing.
//
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//