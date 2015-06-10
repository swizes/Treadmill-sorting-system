/*
 * BandController.h
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#ifndef BANDCONTROLLER_H_
#define BANDCONTROLLER_H_

class BandController {
public:
	virtual ~BandController();
	static CalibrateThread* getInstance();
	void setBandIsStopped(bool stop);
	void setBandRunSlowly(bool slow);

	bool isBandStopped();
	bool isBandRunningSlowly();

private:
	BandController();

	static BandController*  _instance;
	Hal* hal;
	bool stopped;
	bool runSlowly;
};

#endif /* BANDCONTROLLER_H_ */
