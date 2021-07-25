#pragma once
#include "DEFINITIONS.h"
#include "InterfaceC.h"
#include "LooperThreadC.h"
#include <SFML/Graphics.hpp>


class ControllerC
{
public:
	ControllerC();
	int run();

private:
	void kickOffLooperThread(int iThread);
	void drawBaseWindow();

	InterfaceC m_gui_interface;
	LooperThreadC m_Looper[MAX_NUMBER_OF_TRACKS];
};

