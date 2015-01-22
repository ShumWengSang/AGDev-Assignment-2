#include "Camera2.h"
#include <iostream>


Camera::Camera(void)
: MAXSPEED_MOVE(1.0f)
{
	SetCameraType(LAND_CAM);
	Reset();
	Angle = 0;
	SetPosition(0.0, 2.0, -5.0);
	SetDirection(0.0, 0, -1);
	u = 0; v = 0; u1 = 0; v1 = 0;
	fov = 50;
	onground = true;
	yvel = 0;
	jump = 0;
	gravity = -0.5;
	Distance = 6;
	u2 = 0; v2 = 0;
	Reset();



}

Camera::Camera(CAM_TYPE ct)
: MAXSPEED_MOVE(1.0f)
{
	SetCameraType(ct);
	Reset();
	SetPosition(0.0, 2.0, -5.0);
	Angle = 0;
	SetPosition(0.0, 2.0, -5.0);
	SetDirection(0.0, 0, -1);
	u = 0; v = 0; u1 = 0; v1 = 0;
	fov = 50;
	onground = true;
	yvel = 0;
	jump = 0;
	gravity = -0.5;
	Distance = 6;
	u2 = 0; v2 = 0;
	Reset();
}

Camera::~Camera(void)
{
}

void Camera::SetCameraType(CAM_TYPE ct) {
	CameraType = ct;
}

void Camera::Reset(void)
{
	Position = CVector3(0.0, 0.0, 0.0);
	Along = CVector3(1.0, 0.0, 0.0);
	Up = CVector3(0.0, 1, 0.0);
	Forward = CVector3(0.0, 0, 1);
	//	Update();

	MAXSPEED_MOVE = 1.0f;
}

void Camera::Update() {

	gluLookAt(Position.x, Position.y, Position.z,
		Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z,
		0.0f, 1.0f, 0.0f);
}

void Camera::Update(CVector3 theTarget, CVector3 theTargetDir, float angle) {

	CVector3 Temp1, Temp2;


	Temp1 = theTarget - (Forward.NormalizedVector3D() * Distance) + Up.NormalizedVector3D() * 7 + Along * 0;
	SetPosition(Temp1);

	Temp2 = theTarget + (theTargetDir.NormalizedVector3D() * Distance) + Up.NormalizedVector3D() * 4 + Along * 0;

	gluLookAt(Position.x, Position.y, Position.z,
		Temp2.x, Temp2.y, Temp2.z,
		0, 1, 0);
}

void Camera::SetPosition(CVector3 theNewPos)
{
	this->Position.Set(theNewPos);
}

CVector3 Camera::GetPosition() {
	return Position;
}

void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	//Code here to find position of camera.
	//CVector3 camerapos = CalculateDistance(CVector3(x, y, z));

	this->Position.Set(x, y, z);
}

void Camera::SetDirection(GLfloat x, GLfloat y, GLfloat z)
{
	this->Forward.Set(x, y, z);
}

void Camera::SetDirection(CVector3 theNewDir)
{
	this->Forward.Set(theNewDir);
}

void Camera::Pitch(GLfloat theta)
{
	Forward.y -= theta;
	if (Forward.y > 3.142f)
		Forward.y = 3.142f;
	else if (Forward.y < -3.142f)
		Forward.y = -3.142f;
}
void Camera::Yaw(GLfloat theta)
{
	Forward.x = sin(-theta);
	Forward.z = -cos(-theta);
}
void Camera::Roll(GLfloat theta)
{
}
void Camera::Walk(GLfloat delta, bool mode)
{
	if (mode){
		if (delta > MAXSPEED_MOVE)
			delta = MAXSPEED_MOVE;
	}
	else{
		if (delta < -MAXSPEED_MOVE)
			delta = -MAXSPEED_MOVE;
	}
	Position.Set(Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta);
}
void Camera::Strafe(GLfloat delta, bool mode)
{
	if (mode){
		if (delta > MAXSPEED_MOVE)
			delta = MAXSPEED_MOVE;
	}
	else{
		if (delta < -MAXSPEED_MOVE)
			delta = -MAXSPEED_MOVE;
	}
	Along = Along.Cross(Along, Up);
	Along = Along.NormalizedVector3D();
	Position.Set(Position.x + Along.x * delta,
		Position.y + Along.y * delta,
		Position.z + Along.z * delta);


}
void Camera::Fall(float vel)
{
	Position.Set(Position.x, Position.y - vel, Position.z);
}

// Toggle HUD mode
void Camera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	}
	else
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}
}

// Get the direction of the camera
CVector3 Camera::GetDirection(void)
{
	return Forward;
}

void Camera::moveMeForward(bool mode, float timeDiff)
{
	if (mode)
	{
		u = v;
		v = u + 1.f * timeDiff;

		Walk(v, true);

	}
	else
	{
		u = v;
		v = u - 1.f  * timeDiff;

		Walk(v, false);
	}
}

void Camera::moveMeSideway(bool mode, float timeDiff)
{
	if (mode)
	{
		u1 = v1;
		v1 = u1 + 1.f * timeDiff;
		Strafe(v1, true);
	}
	else
	{
		u1 = v1;
		v1 = u1 - 1.f * timeDiff;
		Strafe(v1, false);

	}
}

void Camera::calculations(float diffX, float diffY)
{
	Pitch(diffY * 3.142f / 180.0f);

	Angle += (float)diffX * 3.142f / 180.0f;
	if (Angle > 6.284f)
		Angle -= 6.284f;
	else if (Angle < -6.284f)
		Angle += 6.284f;

	Yaw(-Angle);
}

void Camera::deceleratestraight(float timeDiff)
{
	if (v > 0)
	{
		v = u - 3.f * timeDiff;
		if (v < 0)
		{

			v = u = 0;
		}
	}
	else if (v < 0)
	{
		v = u + 3.f * timeDiff;
		if (v > 0)
		{
			v = u = 0;
		}
	}

	Walk(v, true);

	u = v;
}

void Camera::deceleratesideways(float timeDiff)
{
	if (v1 > 0)
	{
		v1 = u1 - 3.f * timeDiff;
		if (v1 < 0)
		{

			v1 = u1 = 0;
		}
	}
	else if (v1 < 0)
	{
		v1 = u1 + 3.f * timeDiff;
		if (v1 > 0)
		{
			v1 = u1 = 0;
		}
	}

	Strafe(v1, true);

	u1 = v1;
}

void Camera::recoil(float y_recoil, float x_recoil)
{
	CVector3 temp(GetDirection());
	SetDirection(temp.x + x_recoil, temp.y + y_recoil, temp.z);

}

void Camera::setFOV(float fov)
{
	this->fov = fov;
}

void Camera::crouch()
{
	Position.Set(Position.x, Position.y - 100, Position.z);
}

CVector3 Camera::CalculateDistance(CVector3 theFirstPosition)
{
	//First position is position of the object

	//The idea here is to find the direction of the target
	//Than put your camera right behind him.

	//Returns the vector of the position of the camera.

	//First get the direction and than scale it by the distance;
	//This will be where you need to be from the object.
	CVector3 Temp(theFirstPosition);

	Temp = Temp - (Forward.NormalizedVector3D() * Distance) + Up * 5/* + Along * 1*/;
	//Forward = (theFirstPosition - Temp);


	return Temp;
}

void Camera::RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z)
{
	CVector3 vNewPosition;

	// To rotate our position around a point, what we need to do is find
	// a vector from our position to the center point we will be rotating around.
	// Once we get this vector, then we rotate it along the specified axis with
	// the specified degree.  Finally the new vector is added center point that we
	// rotated around (vCenter) to become our new position. Why so much math?

	// Get the vVector from our position to the center we are rotating around
	CVector3 vPos = Position - vCenter;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewPosition.x = (cosTheta + (1 - cosTheta) * x * x)		* vPos.x;
	vNewPosition.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vPos.y;
	vNewPosition.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vPos.z;

	// Find the new y position for the new rotated point
	vNewPosition.y = ((1 - cosTheta) * x * y + z * sinTheta)	* vPos.x;
	vNewPosition.y += (cosTheta + (1 - cosTheta) * y * y)		* vPos.y;
	vNewPosition.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vPos.z;

	// Find the new z position for the new rotated point
	vNewPosition.z = ((1 - cosTheta) * x * z - y * sinTheta)	* vPos.x;
	vNewPosition.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vPos.y;
	vNewPosition.z += (cosTheta + (1 - cosTheta) * z * z)		* vPos.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated position of our camera.
	Position = vCenter + vNewPosition;

	//Forward.Set(( vCenter - Position).NormalizedVector3D());
}

void Camera::ThirdPersonRotation(float& angle)
{
	angle -= 40;
}