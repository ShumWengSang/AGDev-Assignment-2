#pragma once

#include "gl.h"
#include "MVC_Model.h"
#include "Mouse.h"
#include "MVCtime.h"

class MVC_Model;

class MVC_View
{
public:
	static MVC_View * GetInstance(MVC_Model * theModel)
	{
		if(Singleton == 0)
		{
			Singleton = new MVC_View(theModel);
		}
		return Singleton;
	}
	static void Drop()
	{
		if(Singleton != NULL)
		{
			delete Singleton;
			Singleton = NULL;
		}
	}


	~MVC_View(void);
	// Draw the view
	BOOL Draw(void);

	int InitGL(GLvoid);										// All Setup For OpenGL Goes Here
	BOOL CreateGLWindow(char* title, int width, int height, int bits);
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// Resize And Initialize The GL Window
	GLvoid KillGLWindow(GLvoid);

	bool GetkeyState(int);
	bool* GetKeyBuffer();
	void GetSize(int* x,int* y);

	CMouse * m_MouseInfo;
	float m_Swidth,m_Sheight;
private:
	static MVC_View * Singleton;
	MVC_View(MVC_Model* theModel);
	GLuint  m_base;                           // Base Display List For The Font Set


	MVC_Model* m_theModel;

	HDC m_hDC; // Private GDI Device Context
	HGLRC m_hRC; // Permanent Rendering Context
	HWND m_hWnd; // Holds Our Window Handle
	HINSTANCE m_hInstance; // Holds The Instance Of The Application

	bool m_bActive; // Window Active Flag Set To TRUE By Default
	bool m_bFullScreen; // Fullscreen Flag Set To Fullscreen Mode By Default
	bool m_keys[256]; // Array Used For The Keyboard Routine


	void BuildFont(void);
	void KillFont(void);

	virtual LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
public:
	void Printw (float x, float y,const char* format, ...);
	int m_iWindows_Width, m_iWindows_Height;
	void GetDefaultRes(int& height,int& width);
	// Check if the player wants to quit the game
	bool IsQuitGame(void);
	// Check if the player wants to play the game in Full Screen
	bool RunFullScreen(void);
	// Toggle the game to be fullscreen or otherwise
	bool ToggleFullScreen(void);
	// Set the fullscreen display status
	void SetFullScreen(bool m_bFullScreen);

	void DrawScene();
	void DrawObject();
	void MVC_View::Draw3DSGrid();

	friend static int L_PrintDebug(lua_State *state);
};
