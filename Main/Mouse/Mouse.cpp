#include "Mouse.h"


CMouse::CMouse(void)
{
}

CMouse::~CMouse(void)
{
	instanceFlag = false;
}

CMouse* CMouse::getInstance(int num)
{
    if(singleton[num]==0)
    {
        singleton[num] = new CMouse();
        instanceFlag = true;

    }
    return singleton[num];
}		
int CMouse::instanceFlag = 0;
CMouse* CMouse::singleton[3] = {0,0,0};