//***********************************************************************//
//																		 //
//		- "Talk to me like I'm a 3 year old!" Programming Lessons -		 //
//                                                                       //
//		$Author:		DigiBen		digiben@gametutorials.com			 //
//																		 //
//		$Program:		Octree3	 										 //
//																		 //
//		$Description:	A working octree with a .3ds file format scene   //
//																		 //
//***********************************************************************//

#pragma comment(lib, "winmm.lib")

#include "main.h"
#include "Camera.h"

// This is how fast our camera moves
#define kSpeed	5.0f									

///////////////////////////////// CALCULATE FRAME RATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function calculates the frame rate and time intervals between frames
/////
///////////////////////////////// CALCULATE FRAME RATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CalculateFrameRate()
{
	static int framesPerSecond = 0;				// This will store our fps
	static float fpsTime = 0.0f;				// Amount of elapsed time until we update the FPS count
	char strFrameRate[50] = {0};				// We will store the string here for the window title

	// Increase the fps elapsed time
	fpsTime += g_DT;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
	if( fpsTime > 1.0f )
	{
		// Reset the fpsTime
		fpsTime = 0.0f;

		// Copy the frames per second into a string to display in the window title bar
		sprintf(strFrameRate, "Current Frames Per Second: %d", framesPerSecond);

		// Set the window title bar to our string
		SetWindowText(g_hWnd, strFrameRate);

		// Reset the frames per second
		framesPerSecond = 0;
	}
	else
	{
		// Increase the frame counter
		++framesPerSecond;
	}
}


///////////////////////////////// CCAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This is the class constructor
/////
///////////////////////////////// CCAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CCamera::CCamera(CameraType theType)
{
	CVector3 vZero = CVector3(0.0, 0.0, 0.0);		// Init a vVector to 0 0 0 for our position
	CVector3 vView = CVector3(0.0, 1.0, 0.5);		// Init a starting view vVector (looking up and out the screen) 
	CVector3 vUp   = CVector3(0.0, 0.0, 1.0);		// Init a standard up vVector (Rarely ever changes)

	m_vPosition	= vZero;					// Init the position to zero
	m_vView		= vView;					// Init the view to a std starting view
	m_vUpVector	= vUp;						// Init the UpVector

	this->theType = theType;
}

CCamera::~CCamera()
{

}


///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function sets the camera's position and view and up vVector.
/////
///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::PositionCamera(float positionX, float positionY, float positionZ,
				  		     float viewX,     float viewY,     float viewZ,
							 float upVectorX, float upVectorY, float upVectorZ)
{
	CVector3 vPosition	= CVector3(positionX, positionY, positionZ);
	CVector3 vView		= CVector3(viewX, viewY, viewZ);
	CVector3 vUpVector	= CVector3(upVectorX, upVectorY, upVectorZ);

	// The code above just makes it cleaner to set the variables.
	// Otherwise we would have to set each variable x y and z.

	m_vPosition = vPosition;					// Assign the position
	m_vView     = vView;						// Assign the view
	m_vUpVector = vUpVector;					// Assign the up vector
}


///////////////////////////////// SET VIEW BY MOUSE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This allows us to look around using the mouse, like in most first person games.
/////
///////////////////////////////// SET VIEW BY MOUSE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::SetViewByMouse()
{
	POINT mousePos;									// This is a window structure that holds an X and Y
	int middleX = SCREEN_WIDTH  >> 1;				// This is a binary shift to get half the width
	int middleY = SCREEN_HEIGHT >> 1;				// This is a binary shift to get half the height
	float angleY = 0.0f;							// This is the direction for looking up or down
	float angleZ = 0.0f;							// This will be the value we need to rotate around the Y axis (Left and Right)
	static float currentRotX = 0.0f;
	
	// Get the mouse's current X,Y position
	GetCursorPos(&mousePos);						
	
	// If our cursor is still in the middle, we never moved... so don't update the screen
	if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;

	// Set the mouse position to the middle of our window
	SetCursorPos(middleX, middleY);							

	// Get the direction the mouse moved in, but bring the number down to a reasonable amount
	angleY = (float)( (middleX - mousePos.x) ) / 500.0f;		
	angleZ = (float)( (middleY - mousePos.y) ) / 500.0f;		

	static float lastRotX = 0.0f; 
 	lastRotX = currentRotX; // We store off the currentRotX and will use it in when the angle is capped
	
	// Here we keep track of the current rotation (for up and down) so that
	// we can restrict the camera from doing a full 360 loop.
	currentRotX += angleZ;
 
	// If the current rotation (in radians) is greater than 1.0, we want to cap it.
	if(currentRotX > 1.0f)     
	{
		currentRotX = 1.0f;
		
		// Rotate by remaining angle if there is any
		if(lastRotX != 1.0f) 
		{
			// To find the axis we need to rotate around for up and down
			// movements, we need to get a perpendicular vector from the
			// camera's view vector and up vector.  This will be the axis.
			// Before using the axis, it's a good idea to normalize it first.
			CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = Normalize(vAxis);
				
			// rotate the camera by the remaining angle (1.0f - lastRotX)
			RotateView( 1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	// Check if the rotation is below -1.0, if so we want to make sure it doesn't continue
	else if(currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		
		// Rotate by the remaining angle if there is any
		if(lastRotX != -1.0f)
		{
			// To find the axis we need to rotate around for up and down
			// movements, we need to get a perpendicular vector from the
			// camera's view vector and up vector.  This will be the axis.
			// Before using the axis, it's a good idea to normalize it first.
			CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = Normalize(vAxis);
			
			// rotate the camera by ( -1.0f - lastRotX)
			RotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	// Otherwise, we can rotate the view around our position
	else 
	{	
		// To find the axis we need to rotate around for up and down
		// movements, we need to get a perpendicular vector from the
		// camera's view vector and up vector.  This will be the axis.
		// Before using the axis, it's a good idea to normalize it first.
		CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
		vAxis = Normalize(vAxis);
	
		// Rotate around our perpendicular axis
		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	// Always rotate the camera around the y-axis
	RotateView(angleY, 0, 1, 0);
}


///////////////////////////////// ROTATE AROUND POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This rotates the position around a given point
/////
///////////////////////////////// ROTATE AROUND POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z)
{
	CVector3 vNewPosition;

	// To rotate our position around a point, what we need to do is find
	// a vector from our position to the center point we will be rotating around.
	// Once we get this vector, then we rotate it along the specified axis with
	// the specified degree.  Finally the new vector is added center point that we
	// rotated around (vCenter) to become our new position.  That's all it takes.

	// Get the vVector from our position to the center we are rotating around
	CVector3 vPos = m_vPosition - vCenter;

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
	m_vPosition = vCenter + vNewPosition;
}

///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This rotates the view around the position using an axis-angle rotation
/////
///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;

	// Get the view vector (The direction we are facing)
	CVector3 vView = m_vView - m_vPosition;		

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

	// Find the new y position for the new rotated point
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

	// Find the new z position for the new rotated point
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	m_vView = m_vPosition + vNewView;
}


///////////////////////////////// STRAFE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This strafes the camera left and right depending on the speed (-/+)
/////
///////////////////////////////// STRAFE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::StrafeCamera(float speed)
{	
	// Add the strafe vector to our position
	m_vPosition.x += m_vStrafe.x * speed;
	m_vPosition.z += m_vStrafe.z * speed;

	// Add the strafe vector to our view
	m_vView.x += m_vStrafe.x * speed;
	m_vView.z += m_vStrafe.z * speed;
}


///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This will move the camera forward or backward depending on the speed
/////
///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::MoveCamera(float speed)
{
	// Get the current view vector (the direction we are looking)
	CVector3 vVector = m_vView - m_vPosition;
	vVector = Normalize(vVector);

	m_vPosition.x += vVector.x * speed;		// Add our acceleration to our position's X
	m_vPosition.y += vVector.y * speed;		// Add our acceleration to our position's Y
	m_vPosition.z += vVector.z * speed;		// Add our acceleration to our position's Z
	m_vView.x += vVector.x * speed;			// Add our acceleration to our view's X
	m_vView.y += vVector.y * speed;			// Add our acceleration to our view's Y
	m_vView.z += vVector.z * speed;			// Add our acceleration to our view's Z
}


//////////////////////////// CHECK FOR MOVEMENT \\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function handles the input faster than in the WinProc()
/////
//////////////////////////// CHECK FOR MOVEMENT \\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::CheckForMovement()
{	
	// Once we have the frame interval, we find the current speed
	float speed = kSpeed * g_DT;
	float rotatespeed = 3.0f * g_DT;

	// Check if we hit the Up arrow or the 'w' key
	if(GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80) {				

		// Move our camera forward by a positive SPEED
		MoveCamera(speed);				
	}

	// Check if we hit the Down arrow or the 's' key
	if(GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80) {			

		// Move our camera backward by a negative SPEED
		MoveCamera(-speed);				
	}

	if (theType == CameraType::ThirdPerson)
	{
		// Check if we hit the Left arrow or the 'a' key
		if (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80) {

			// Strafe the camera left
			RotateAroundPoint(m_vView, rotatespeed, 0, 1, 0);
		}

		// Check if we hit the Right arrow or the 'd' key
		if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80) {

			// Strafe the camera right
			RotateAroundPoint(m_vView, rotatespeed, 0, -1, 0);
		}
	}
	else if (theType == CameraType::FirstPerson)
	{
		// Check if we hit the Left arrow or the 'a' key
		if (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80) {

			// Strafe the camera left
			StrafeCamera(-speed);
		}

		// Check if we hit the Right arrow or the 'd' key
		if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80) {

			// Strafe the camera right
			StrafeCamera(speed);
		}
	}
}


///////////////////////////////// UPDATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This updates the camera's view and strafe vector
/////
///////////////////////////////// UPDATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::Update() 
{
	// Initialize a variable for the cross product result
	CVector3 vCross = Cross(m_vView - m_vPosition, m_vUpVector);

	// Normalize the strafe vector
	m_vStrafe = Normalize(vCross);

	if (theType == CameraType::FirstPerson)
	{
		// Move the camera's view by the mouse
		SetViewByMouse();
	}

	// This checks to see if the keyboard was pressed
	CheckForMovement();
	
	// Calculate our frame rate and set our frame interval for time based movement
	CalculateFrameRate();
}


///////////////////////////////// LOOK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This updates the camera according to the 
/////
///////////////////////////////// LOOK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CCamera::Look()
{
	// Give openGL our camera position, then camera view, then camera up vector
	gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,	
			  m_vView.x,	 m_vView.y,     m_vView.z,	
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// Nothing was changed since the Time Based Movement tutorial, except in
// MoveCamera() we allowed the user to enter fly mode with using the Y value.
// The 1000 was changed to 500 in SetViewByMouse() to make the camera faster.
//
//
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//
