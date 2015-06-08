#include "HoleDetector.h"
#include "HAL.h"
#include <iostream>

using namespace std;

	static int max_ground_height = 900;
	static int min_puck_height = 2600;
	static int min_hole_diff = 500;
	static long max_runthrough_time_fast = 20000;
	static long max_runthrough_time_slow = 50000;

bool HoleDetector::detectHole(HAL *hal, bool runningSlow) {
	int measured_max_height = 0;
	int measured_min_height = 0;
	int mheight, puckheight0, puckheight1;
	int elapsed_time = 0;
	int max_time = runningSlow ? max_runthrough_time_slow : max_runthrough_time_fast;

	/*
	max_ground_height = 900;
	min_puck_height = 2000;
	min_hole_diff = 500;
	max_runthrough_time_fast = 20000;
	max_runthrough_time_slow = 50000;
	 */
	bool foundHole = false, puckComplete = false;

	// wait for puck entry
	mheight = hal->get_height_measure();

	while(mheight > min_puck_height) {
		cout << "w1 (" << mheight << " > " << min_puck_height << ") [t: " << elapsed_time << "]" << endl;
		mheight = hal->get_height_measure();
	}
	cout << "p1" << endl;
	puckheight0 = mheight;

	// mark time puck entry

	// wait for hole or time up
	while ((mheight = hal->get_height_measure()) < (puckheight0 + min_hole_diff) && elapsed_time < max_time) {
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
	while ((mheight = hal->get_height_measure()) > min_puck_height && elapsed_time < max_time)
	{
		cout << "w3 (" << mheight << " > " << min_puck_height << ") [t: " << elapsed_time << "]" << endl;
	}
	cout << "p3" << endl;
	if(mheight < min_puck_height)
	{
		puckComplete = true;
	}

	return foundHole && puckComplete;
}
