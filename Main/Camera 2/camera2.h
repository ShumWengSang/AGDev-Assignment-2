#pragma once


#include <stdio.h>
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
#include "Vector3.h"
class Camera
{
public:
	enum CAM_TYPE { LAND_CAM, AIR_CAM };

private:
	CAM_TYPE CameraType;
	CVector3 Position;
	CVector3 Along;
	CVector3 Up;
	CVector3 Forward;
	float Angle;
	
public:
	Camera(void);
	Camera(CAM_TYPE ct);
	~Camera(void);

	void SetCameraType(CAM_TYPE ct);
	void Reset(void);
	void Update();
	void Update(CVector3 theTarget, CVector3, float angle);
	CVector3 GetPosition();
	// Get the direction of the camera
	CVector3 GetDirection(void);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetPosition(CVector3 theNewPos);
	void SetDirection(GLfloat x, GLfloat y, GLfloat z);
	void SetDirection(CVector3 theNewDir);
	void calculations(float diffX, float diffY);

	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	void Walk(GLfloat delta, bool mode);
	void Strafe(GLfloat delta, bool mode);
	void Fall(float vel);

	void setFOV(float fov);
	float fov;

	// Toggle HUD mode
	void SetHUD(bool m_bHUDmode);

	void moveMeForward(bool mode, float timeDiff);
	void moveMeSideway(bool mode, float timeDiff);

	void deceleratestraight(float timeDiff);
	void deceleratesideways(float timeDiff);

	void recoil( float y_recoil, float x_recoil );
	void crouch();

	void RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z);

	bool onground;
	float yvel, jump, gravity;
	float Distance;

	void ThirdPersonRotation(float& angle);
	void Rotateme(bool mode, float timeDiff, float &angle);

private:
	// Maximum movement speed
	float MAXSPEED_MOVE;
	
	//VARIABLES FOR ACCELERATION AND DECELERATION
	float u, u1, v, v1;

	CVector3 CalculateDistance(CVector3 theFirstPosition);
	float u2, v2;
	
};

