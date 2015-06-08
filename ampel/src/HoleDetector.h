#ifndef HOLEDETECTOR_H_
#define HOLEDETECTOR_H_

class HAL;

class HoleDetector {
	
public:
	static bool detectHole(HAL *hal, bool runningSlow);
};

#endif /* HOLEDETECTOR_H */
