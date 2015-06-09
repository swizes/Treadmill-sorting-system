#include "HoleDetector.h"
#include "HAL.h"
#include <iostream>

using namespace std;

	static int max_ground_height = 900;
	static int min_puck_height = 2600;
	static int min_hole_diff = 500;
	static long max_runthrough_time_fast = 2;
	static long max_runthrough_time_fast_ms = 2;
	static long max_runthrough_time_slow = 5;
	static long max_runthrough_time_slow_ms = 5;

bool HoleDetector::detectHole(HAL *hal, bool runningSlow) {
	int measured_max_height = 0;
	int measured_min_height = 0;
	int mheight, puckheight0, puckheight1;
	int elapsed_time = 0;
	int max_time = runningSlow ? max_runthrough_time_slow : max_runthrough_time_fast;
	int max_time_ms = runningSlow ? max_runthrough_time_slow_ms : max_runthrough_time_fast_ms;

	max_time *= 1000;
	max_time += max_time_ms;

	bool foundHole = false, puckComplete = false;

	Timer timer;
	timer.createTimer();
	timer.setTimer(max_time, max_time_ms*1000);
	struct timespec result;

	// wait for puck entry
	mheight = hal->get_height_measure();

	while(mheight > min_puck_height) {
		timer.getTime(&result);
		elapsed_time = result.tv_sec * 1000;
		elapsed_time += result.tv_nsec / 1000;
		cout << "w1 (" << mheight << " > " << min_puck_height << ") [t: " << elapsed_time << "]" << endl;
		mheight = hal->get_height_measure();
	}
	cout << "p1" << endl;
	puckheight0 = mheight;

	// mark time puck entry

	// wait for hole or time up
	while ((mheight = hal->get_height_measure()) < (puckheight0 + min_hole_diff) && elapsed_time > 0) {
		timer.getTime(&result);
		elapsed_time = result.tv_sec * 1000;
		elapsed_time += result.tv_nsec / 1000;
		cout << "w2 (" << mheight << " < " << (puckheight0 + min_hole_diff) << " [" << puckheight0 << "+" <<  min_hole_diff << "] [t: " << elapsed_time << "]" << endl;
		if(mheight > puckheight0) puckheight0 = mheight;
	}
	cout << "p2" << endl;
	cout << "w2-> (" << mheight << " > " << (puckheight0 + min_hole_diff) << " [" << puckheight0 << "+" <<  min_hole_diff << "] [t: " << elapsed_time << "]" << endl;
	if(mheight > (puckheight0 + min_hole_diff))
	{
		foundHole = true;
	} else {
		return false;
	}

	// wait for puck hole end
	while ((mheight = hal->get_height_measure()) > min_puck_height && elapsed_time > 0)
	{
		timer.getTime(&result);
		elapsed_time = result.tv_sec * 1000;
		elapsed_time += result.tv_nsec / 1000;
		cout << "w3 (" << mheight << " > " << min_puck_height << ") [t: " << elapsed_time << "]" << endl;
	}
	cout << "p3" << endl;
	if(mheight < min_puck_height)
	{
		puckComplete = true;
	}

	return foundHole && puckComplete;
}
