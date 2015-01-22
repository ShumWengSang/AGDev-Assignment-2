
#include "MVC_Model.h"
#include "MVC_View.h"
#include "MVC_Controller.h"
//#include "gl.h"
#define _CRT_SECURE_NO_DEPRECATE

//#pragma comment (lib,"Math")
//#pragma comment (lib,"Model and Texture Loader")
//#pragma comment (lib,"GLU32.lib")

int main( int argc, char* args )
{
	MVC_Model* theModel = new MVC_Model();
	MVC_View* theView = new MVC_View( theModel );
	MVC_Controller* theController = new MVC_Controller( theModel, theView );
	if(!theController->Init())
		return 1;
	else
		theController->RunMainLoop();

	if ( theController != NULL)
	{
		delete theController;
		theController = NULL;
	}
	if ( theView != NULL)
	{
		delete theView;
		theView = NULL;
	}
	if ( theModel != NULL)
	{
		delete theModel;
		theModel = NULL;
	}
	return 0;
}