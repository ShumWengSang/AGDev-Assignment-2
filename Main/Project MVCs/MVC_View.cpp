//*************************************************************************************************************************************//
//
//	Original MVC framework made by Mr Toh Da Jun for DM2231 Game Development Techniques
//	Adapted and modified by Kennard Kee Wei Sheng
//	Framework taken with permission by Shum Weng Sang
//************************************************************************************************************************************//
#include "MVC_View.h"

static int L_GetCamnFPS(lua_State *state)
{
	int n = lua_gettop(state);

	// check if number of arguments is less than 4
	// then we stop as not enough parameters
	if(n != 0)
	{
		std::cout << "Error: nothing." << std::endl;
		lua_error(state);
		return 0;
	}

	MVC_Model * theModel = MVC_Model::GetInstace();

	if(theModel->DebugCam)
	{
		theModel->theInterface->Push(theModel->Camera2.Position());
	}
	else
	{
		theModel->theInterface->Push(theModel->theCamera.Position());
	}
	theModel->theInterface->Push(theModel->m_timer->GetFPS());


	return 4;
}

static int L_PrintDebug(lua_State *state)
{
	MVC_View * theView = MVC_View::GetInstance(MVC_Model::GetInstace());

	int n = lua_gettop(state);

	// check if number of arguments is less than 4
	// then we stop as not enough parameters
	if(n < 3)
	{
		std::cout << "Error: printDebug(number,number, char *, ... )" << std::endl;
		lua_error(state);
	}

	// gets parameter
	//int x = lua_tointeger(state, 1);
	//int y = lua_tointeger(state, 2);
	//char * words = (char*) lua_tostring(state, 3);


	char text[256]; /* Be careful! Buffer overflow potential for not checking lengths of sprintf and not using snprintf */
	char *buf = &text[0]; /* start buf at beginning of text */
	int x = lua_tointeger(state, 1);
	int y = lua_tointeger(state, 2);
	for (int i = 3; i < n + 1; i++)
	{
		if (lua_type(state,i) == LUA_TNUMBER) {
			sprintf(buf, "%f", lua_tonumber(state,i));
		} else if (lua_type(state,i) == LUA_TSTRING) {
			sprintf(buf, "%s", lua_tostring(state,i));
		} else {
			// ERROR SOMEHOW
		}
		buf += strlen(buf); /* Move the end of buf for more appending
							}
							/* At this point, we've filled in text by walking through it with our buf pointer, and we have a complete string */
		glRasterPos2f(x,y);
		glPushAttrib(GL_LIST_BIT);
		glListBase(theView->m_base-32);
		glCallLists(strlen(text),GL_UNSIGNED_BYTE,text);
		glPopAttrib();
	}
	return 1;
}

static int L_Update(lua_State *state)
{
	
	return 1;
}

MVC_View::MVC_View(MVC_Model* theModel)
{
	m_theModel = theModel;
	m_MouseInfo = CMouse::getInstance(0);
	m_MouseInfo->init();
	m_iWindows_Width = 1; 
	m_iWindows_Height = 1;
	m_Sheight=100;
	m_Swidth=150;

	m_bActive = true; // Window Active Flag Set To TRUE By Default
	m_bFullScreen = false; // Fullscreen Flag Set To Fullscreen Mode By Default

	m_hDC=NULL;
	m_hRC=NULL;
	m_hWnd=NULL;

	for (int i=0; i<256; i++)
	{
		m_keys[i] = false;
	}

	m_theModel->Camera2.GetKeys(GetKeyBuffer());

	m_theModel->theInterface->Pushfunction("PrintOnScreen",L_PrintDebug);
}

MVC_View::~MVC_View(void)
{
	m_theModel = NULL;
}

// Draw the view
BOOL MVC_View::Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity(); // ReSet The Current Modelview Matrix
	glColor3f(1,1,1);

	//m_theModel->theFirstCamera.Update();
	if(m_theModel->DebugCam)
		m_theModel->Camera2.Look();
	else
		m_theModel->theCamera.Look();
	//m_theModel->theCamera.Update();
	//m_theModel->thePlayerData.glRenderObject(&m_theModel->theCamera.Position());

	DrawScene();

	glColor3f(1,1,1);
	SwapBuffers(m_hDC); // Swap Buffers (Double Buffering)

	return TRUE; // Keep Going
}

int MVC_View::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	BuildFont();

	return TRUE; // Initialization Went OK
}

void MVC_View::DrawObject()
{
	glPushMatrix();
	glTranslatef(m_theModel->theCamera.Position().x, m_theModel->theCamera.Position().y, m_theModel->theCamera.Position().z);
	glRotatef(Math::VectorToAngle(m_theModel->theCamera.View()), 0.0f, 1.0f, 0.0f); // Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
	glPopMatrix();
}

void MVC_View::DrawScene()
{
	glPushMatrix();
	//m_theModel->theBox.Draw();

	Draw3DSGrid();

	//for (int i = 0; i < m_theModel->theListofObjects.size(); i++)
	//{
	//	m_theModel->theListofObjects[i]->glRenderObject(3);
	//}
	m_theModel->theQuadTree.Draw(&m_theModel->Camera2);


	m_theModel->theHUD.SetHUD(true);
	m_theModel->theHUD.Draw();
	glColor3f(0.0, 0.0, 1.0);
	if(GetKeyState('O') & 0x80)
	{
		m_theModel->theInterface->Pushfunction("GetCamAndFPS",L_GetCamnFPS);
		m_theModel->theInterface->RunScript("Debug.lua");
		//Printw(10, 50, "FPS: %.2f", MVCTime::GetInstance()->GetFPS());
		//Printw(10, 100, "Camera 2 Pos: %f %f %f", m_theModel->Camera2.Position().x, m_theModel->Camera2.Position().y, m_theModel->Camera2.Position().z);
		//Printw(10, 150, "Player Data Pos: %f %f %f", m_theModel->thePlayerData.getPosition().x, m_theModel->thePlayerData.getPosition().y, m_theModel->thePlayerData.getPosition().z);
		//Printw(10, 200, "Player Direction %f %f %f , Angle : %f", m_theModel->thePlayerData.getDirection().x, m_theModel->thePlayerData.getDirection().y, m_theModel->thePlayerData.getDirection().z, Math::VectorToAngle(m_theModel->thePlayerData.getDirection()));
		//Printw(10, 250, "Camera 2 Direction %f %f %f , Angle : %f", m_theModel->Camera2.View().x, m_theModel->Camera2.View().y, m_theModel->Camera2.View().z, Math::VectorToAngle(m_theModel->Camera2.View()));
	}


	//Printw(10, 300, "Distance with Data: %f", (m_theModel->thePlayerData.getPosition() - m_theModel->theCamera.Position()).GetMagnitude());
	m_theModel->theHUD.SetHUD(false);
	glPopMatrix();

}

void MVC_View::Draw3DSGrid()
{
	// This function was added to give a better feeling of moving around.
	// A black background just doesn't give it to ya :)  We just draw 100
	// green lines vertical and horizontal along the X and Z axis.

	// Turn the lines GREEN
	glColor3ub(255, 192, 203);
	glLineWidth(5);
	// Draw a 1x1 grid along the X and Z axis'
	for (float i = -m_theModel->theBox.Width; i <= m_theModel->theBox.Width; i += 1)
	{
		// Start drawing some lines
		glBegin(GL_LINES);

		// Do the horizontal lines (along the X)
		glVertex3f(-100, 0, i);
		glVertex3f(100, 0, i);

		// Do the vertical lines (along the Z)
		glVertex3f(i, 0, -100);
		glVertex3f(i, 0, 100);

		// Stop drawing lines
		glEnd();
	}
	glLineWidth(1);
}

MVC_View * MVC_View::Singleton = NULL;