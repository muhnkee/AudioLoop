#pragma once
#include "DEFINITIONS.h"
#include "InterfaceC.h"
#include "LooperThreadC.h"
#include <SFML/Graphics.hpp>

// Maximum number of looper threads that may be created
// I prefer this to magic numbers in the code
#define MAX_THREADS 4

class ControllerC
{
public:
	ControllerC();
	int run();

private:

	void kickOffLooperThread(int iThread);
	void drawBaseWindow();

	InterfaceC m_gui_interface;
	LooperThreadC *m_Looper[MAX_NUMBER_OF_TRACKS];
};

