#ifndef HOLEDETECTOR_H_
#define HOLEDETECTOR_H_

class HoleDetector {
	static int max_ground_height = 900;
	static int min_puck_height = 2000;
	static int min_hole_diff = 500;
	static long max_runthrough_time_fast = 20000;
	static long max_runthrough_time_slow = 50000;
	
	static bool detectHole(HAL *hal, bool runningSlow);
}

#endif /* HOLEDETECTOR_H */