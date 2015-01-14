#ifndef _MAIN_H
#define _MAIN_H

// In Visual Studio 2005 Microsoft added safer versions (denoted by a "_s" suffix) to many 
// common C/C++ run time functions.  Currently the ISO Standards Committee for C and C++ 
// is determining if they are going to add them to the official language set.  Until then, 
// this define will remove warnings about using the "unsafe" versions of these functions.
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\gl.h>										// Header File For The OpenGL32 Library
#include <gl\glu.h>										// Header File For The GLu32 Library

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *
#include <vector>
using namespace std;

#define SCREEN_WIDTH 800								// We want our screen width 800 pixels
#define SCREEN_HEIGHT 600								// We want our screen height 600 pixels
/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

#define SCREEN_DEPTH 16									// We want 16 bits per pixel

#define MAX_TEXTURES 100								// The maximum amount of textures to load

#include "Vector3.h"

// Because COctree.h needs a reference to CVector3 we include it after the class definition
#include "Octree.h"

// After we include the octree header we should include the frustum header
#include "Frustum.h"

extern bool		g_bFullScreen;							// Set full screen as default
extern HWND		g_hWnd;									// This is the handle for the window
extern RECT		g_rRect;								// This holds the window dimensions
extern HDC		g_hDC;									// General HDC - (handle to device context)
extern HGLRC	g_hRC;									// General OpenGL_DC - Our Rendering Context for OpenGL
extern float g_DT;										// Global float that stores the elapsed time between the current and last frame
extern bool bDebugCamera;


// Extern our debug object because we use it in the octree code
extern class CDebug g_Debug;

// Extern our global frustum object so we can check if our nodes are 
// inside the frustum before we draw them.
extern class CFrustum g_Frustum;

// Extern our global texture array
extern UINT g_Texture[MAX_TEXTURES];

// This is our MAIN() for windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow);

// The window proc which handles all of window's messages.
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// This controls our main program loop
WPARAM MainLoop();

// This creates a texture and stores it in the texture array with it's ID.
bool CreateTexture(GLuint &textureID, LPTSTR szFileName);

// This changes the screen to full screen mode
void ChangeToFullScreen();

// This is our own function that makes creating a window modular and easy
HWND CreateMyWindow(LPSTR szWindowName, int width, int height, DWORD dwStyle, BOOL fullScreen, HINSTANCE hInstance);

// This allows us to configure our window for OpenGL and backbuffered
BOOL bSetupPixelFormat(HDC hdc);

// This inits our screen translations and projections
void SizeOpenGLScreen(int width, int height);

// This sets up OpenGL
void InitializeOpenGL(int width, int height);

// This initializes the whole program
void Init(HWND hWnd);

// This draws everything to the screen
void RenderScene();

// This frees all our memory in our program
void DeInit();

//This updates our game
void Update();

#endif 


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// Nothing new was added to this file for this tutorial except that we included the
// vector file, along with using the std namespace.  We also changed the screen
// resolution from 800 by 600 to 640 by 480.
// 
//
// DigiBen
// Game Programmer
// DigiBen@GameTutorials.com
// www.GameTutorials.com
//
//