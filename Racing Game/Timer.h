#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();

	float Read();
	float ReadSec();

private:

	bool	running;
	float	started_at;
	float	stopped_at;
};

#endif //__TIMER_H__