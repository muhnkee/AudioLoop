#pragma once
#include "LooperC.h"
#include "InterfaceC.h"
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

	InterfaceC gui_interface;
	LooperC testLooper;
};

