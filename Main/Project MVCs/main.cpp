
#include "MVC_Model.h"
#include "MVC_View.h"
#include "MVC_Controller.h"



int main( int argc, char* args )
{
	MVC_Model* theModel = MVC_Model::GetInstace();
	MVC_View* theView = MVC_View::GetInstance(theModel);;
	MVC_Controller* theController = MVC_Controller::GetInstace(theModel,theView);

	if(!theController->Init())
		return 1;
	else
		theController->RunMainLoop();

	MVC_Controller::Drop();
	MVC_View::Drop();
	MVC_Model::Drop();
	return 0;
}