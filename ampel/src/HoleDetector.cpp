#include "HoleDetector.h"

bool HoleDetector::detectHole(HAL *hal, bool runningSlow) {
	int measured_max_height = 0;
	int measured_min_height = 0;
	int mheight;
	
	// wait for puck entry
	while((mheight = hal->get_height_measure()) < min_puck_height) {}
	// mark time puck entry
	while ()
	
	// wait for hole or time up
	
	
	// wait for puck hole end
	
}