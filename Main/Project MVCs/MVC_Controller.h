#pragma once


#include "gl.h"
#include "MVC_Model.h"
#include "MVC_View.h"
#include "MVCtime.h"
#include"ComGTGALoad.h"


class MVC_Model;
class MVC_View;
class MVCTime;

class MVC_Controller
{
public:
	MVC_Controller(MVC_Model* theModel, MVC_View* theView);
	~MVC_Controller(void);

	// Get the status of the stop game boolean flag
	BOOL RunMainLoop(void);

	// Process input from I/O devices
	bool ProcessInput(void);

	inline void SetHandle(HWND hwnd) { m_handle = hwnd; }

	// Handle to the model
	MVC_Model* m_theModel;

	// Handle to the view
	MVC_View* m_theView;

	MVCTime * theTimer;

	bool Init();

protected:
	HWND m_handle;// window handle to map window to controller

	bool m_bContinueLoop;

	int ProcKeys(int);
	void ProcKeyboard();
	void ProcMouse();

	//Boolean used to control the timer on rotation.
	bool ControlRotationTime;

	void RotateCamera(float AngletoChange);
	float v1, u1;

};
