//*************************************************************************************************************************************//
//
//	Original MVC framework made by Mr Toh Da Jun for DM2231 Game Development Techniques
//	Adapted and modified by Kennard Kee Wei Sheng
//	Framework taken with permission by Shum Weng Sang
//************************************************************************************************************************************//

#include "MVC_Controller.h"

#define fps 60

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

MVC_Controller::MVC_Controller(MVC_Model* theModel, MVC_View* theView)
: m_theModel(NULL)
, m_theView(NULL)
, m_bContinueLoop(false)
{
	m_theModel = theModel;
	m_theView = theView;
	theTimer = MVCTime::GetInstance();
	theTimer->PushNewTime(1);
	theTimer->SetLimit(0, 200);
	ControlRotationTime = true;
	v1 = 0; u1 = 0;
}

MVC_Controller::~MVC_Controller(void)
{
	m_theView = NULL;
	m_theModel = NULL;
}

bool MVC_Controller::Init(void)
{


	if(!m_theModel->Init(fps))
		return false;

	return true;
}


// Get the status of the stop game boolean flag
BOOL MVC_Controller::RunMainLoop(void)
{
	//SetCursorPos(m_theView->m_iWindows_Width / 2, m_theView->m_iWindows_Height / 2);
	MSG msg; // Windows Message Structure
	BOOL done=FALSE; // Bool Variable To Exit Loop
		// Ask The User Which Screen Mode They Prefer
	
	m_theModel->theInterface->RunScript("Init.lua");
	std::string name;
	m_theModel->theInterface->Get(name, "title");

	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		m_theView->SetFullScreen( false );
		int height, width;

		m_theModel->theInterface->RunScript("Init.lua");
		m_theModel->theInterface->Get(height, "ScreenHeight");
		m_theModel->theInterface->Get(width, "ScreenWidth");

		// Create Our OpenGL Window
		if (!m_theView->CreateGLWindow((char*)name.c_str(),width,height,16))
		{
			return false;									// Quit If Window Was Not Created
		}
	}
	else
	{
		m_theView->SetFullScreen( true );
		int height,width;
		m_theView->GetDefaultRes(height,width);
		// Create Our OpenGL Window
		if (!m_theView->CreateGLWindow((char*)name.c_str(),width,height,16))
		{
			return false;									// Quit If Window Was Not Created
		}
	}
	
	m_theModel->InitPhase2();

	while(!done) // Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) // Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT) // Have We Received A Quit Message?
			{
				done=TRUE; // If So done=TRUE
			}
			else // If Not, Deal With Window Messages
			{
				TranslateMessage(&msg); // Translate The Message
				DispatchMessage(&msg); // Dispatch The Message
			}
		}
		else // If There Are No Messages
		{
			theTimer->UpdateTime();
			if (ProcessInput())
			{
				m_theModel->Update();
				m_theView->Draw();
			}
			else
			{
				done=TRUE; // ESC or DrawGLScene Signalled A Quit
			}
			//Letting the application sleep once processes can allow it 
			//to process information, drastically improving program.
			//#VALUETOWN
			Sleep(1);
		}
	}

	// Shutdown
	m_theView->KillGLWindow(); // Kill The Window
	return (msg.wParam); // Exit The Program
}

// Process input from I/O devices
bool MVC_Controller::ProcessInput(void)
{
	if (theTimer->TestTime(0,true) && (!m_theModel->DebugCam))
	{
		//Every 0.5 seconds, set the cursor back to normal position.
		//Due to restarting the timer when mouse is moved, it isn't really checking every 0.5 seconds.
		SetCursorPos(m_theView->m_iWindows_Width / 2, m_theView->m_iWindows_Height / 2);
		theTimer->ResetTime(0);
		ControlRotationTime = true;
	}
	
	// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
	if (m_theView->IsQuitGame())				// Was ESC Pressed?
	{
		m_bContinueLoop=false;						// ESC Signalled A Quit
		return false;
	}

	if (m_theView->RunFullScreen())						// Is F1 Being Pressed?
	{
		if (m_theView->ToggleFullScreen() == false)
		{
			m_bContinueLoop=false;						// ESC Signalled A Quit
			return false;
		}
	}
	
	ProcKeyboard();
	
	ProcMouse();
	
	return true;
}

void MVC_Controller::ProcMouse()
{
	int w;
	int h;
	m_theView->GetSize(&w,&h);


	if (!m_theModel->DebugCam)
	{

		//ROTATING CAMERA
		//SINCE SetCursor (in controller in process input) sets the cursor back to the middle every 0.5 seconds
		//We don't have to worry about where the cursor is all the time.
		//If left side, rotate that way. If right side, rotate that way.
		if (m_theView->m_MouseInfo->m_x < (m_theView->m_iWindows_Height / 2))
		{
			//m_theModel->ObjectAngle += -40 * theTimer->GetDelta();
			//RotateCamera(-80);

		}
		else if (m_theView->m_MouseInfo->m_x > (m_theView->m_iWindows_Width / 2))
		{
			//RotateCamera(80);
		}

	}
	if(m_theView->m_MouseInfo->m_LButtonDown)
	{

	}
	else if(m_theView->m_MouseInfo->m_LButtonUp)
	{

	}

	if(m_theView->m_MouseInfo->m_RButtonDown)
	{

	}
	else if(m_theView->m_MouseInfo->m_RButtonUp)
	{
		m_theView->m_MouseInfo->m_RButtonUp=false;
	}
}

int MVC_Controller::ProcKeys(int key)
{
	if(key>=97&&key<122)
	{
		return 0x41+(key-97);
	}
	else if(key>=48&&key<57)
	{
		return 0x30+(key-48);
	}
	return 0;
}

void MVC_Controller::ProcKeyboard()
{
	if(m_theModel->DebugCam)
		m_theModel->Camera2.CheckForMovement();
	else
		m_theModel->theCamera.CheckForMovement();

	bool* temp = m_theView->GetKeyBuffer();

	if (temp[ProcKeys('p')])
	{
		m_theModel->DebugCam = !m_theModel->DebugCam;
		temp[ProcKeys('p')] = false;
	}

	//DEBUG
	if (temp[VK_NUMPAD8])
	{
		
	}
	if (temp[VK_NUMPAD2])
	{
		
	}
	if (temp[VK_F3])
	{
		
	}
	if (temp[VK_F4])
	{
		
	}
	if (temp[VK_ADD])
	{
		
	}
	if (temp[VK_SUBTRACT])
	{
		
	}
	if (temp[VK_SPACE])
	{
		
	}
}

void MVC_Controller::RotateCamera(float AngletoChange)
{
//	u1 = v1;
	//v1 = u1 + AngletoChange * theTimer->GetDelta();

/*	m_theModel->ObjectAngle += AngletoChange * theTimer->GetDelta();

	//Change into Radian, so that we can change into a vector.
	float Angle = Math::degreesToRadians(m_theModel->ObjectAngle);
	CVector3 newDir(cosf(Angle), 0, (sinf(Angle)));

	//Now we have the vector, set it as the player's new direction vector.
	m_theModel->thePlayerData.SetDir(newDir.m_x, newDir.m_y, newDir.m_z);
	//Set as the camera new direction vector. Player and camera direction are now the same.
	m_theModel->theCamera.SetDirection(newDir.m_x, newDir.m_y, newDir.m_z);

	//Now apply the rotation to the Player in the scene graph. Since -40 is the APPLIED rotation,
	//We apply 40 to rotate him in the opposite way.

	m_theModel->theRoot.GetNode(m_theModel->PlayerID)->ApplyRotate(-AngletoChange * theTimer->GetDelta(), 0, 1, 0);

	if (m_theModel->thePlayerData.ToggleFrustum)
	{
		m_theModel->theFrustum.Update(m_theModel->thePlayerData.GetPos(), m_theModel->thePlayerData.GetDir());
	}
	//Timer to reset, so that we check if the player is moving his mouse 
	//in the direction for 0.5 seconds.
	if (ControlRotationTime)
	{
		ControlRotationTime = false;
		theTimer->ResetTime(0);
	}
	*/
}

MVC_Controller * MVC_Controller::Singleton = NULL;
