#pragma once
// Maximum number of looper threads that may be created
// I prefer this to magic numbers in the code
#define MAX_THREADS 4

class ControllerC
{
public:
	int run();

private:
	void kickOffLooperThread(int iThread);
	void drawBaseWindow();

};

