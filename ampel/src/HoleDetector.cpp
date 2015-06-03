#include "HoleDetector.h"
#include "HAL.h"

bool HoleDetector::detectHole(HAL *hal, bool runningSlow) {
	int measured_max_height = 0;
	int measured_min_height = 0;
	int mheight, puckheight;
	int elapsed_time = 0;
	int max_time = runningSlow ? max_runthrough_time_slow : max_runthrough_time_fast;

	bool foundHole = false, puckComplete = false;

	// wait for puck entry
	while((mheight = hal->get_height_measure()) < min_puck_height) {cout << "w1 (" << mheight << " < " << min_puck_height << ") [t: " << elapsed_time << "]" << endl;}
	puckheight = mheight;

	// mark time puck entry

	// wait for hole or time up
	while ((mheight = hal->get_height_measure()) > (puckheight - min_hole_diff) && elapsed_time < max_time) {
		cout << "w2 (" << mheight << " > " << (puckheight - min_hole_diff) << " [" << puckheight << "-" <<  min_hole_diff << "] [t: " << elapsed_time << "]" << endl;
		if(mheight > puckheight) puckheight = mheight;
	}
	
	if(mheight < puckheight - min_hole_diff)
	{
		foundHole = true;
	} else {
		return false;
	}

	// wait for puck hole end
	while ((mheight = hal->get_height_measure()) < min_puck_height && elapse_time < max_time)
	{
		cout << "w1 (" << mheight << " < " << min_puck_height << ") [t: " << elapsed_time << "]" << endl;
	}

	if(mheight > min_puck_height)
	{
		puckComplete = true;
	}

	return foundHole && puckComplete;
}
