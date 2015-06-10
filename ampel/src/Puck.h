/*
 * Puk.h
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#ifndef PUCK_H_
#define PUCK_H_

enum SIZE{OK,NOT_OK,UNKNOWN};

class Puck {

private:
	bool metal;
	bool holeOnTop;
	int size;
	SIZE sizeTyp;
	int id;
	static int idCount;

public:
	Puck();
	virtual ~Puck();

	bool isHoleOnTop() const {
		return holeOnTop;
	}

	void setHoleOnTop(bool holeOnTop) {
		this->holeOnTop = holeOnTop;
	}

	bool isMetal() const {
		return metal;
	}

	void setMetal(bool metal) {
		this->metal = metal;
	}

	int getSize() const {
		return size;
	}

	void setSize(int size) {
		this->size = size;
	}

	int getId() const {
		return id;
	}


	SIZE getSizeTyp() const {
		return sizeTyp;
	}

	void setSizeTyp(SIZE sizeTyp) {
		this->sizeTyp = sizeTyp;
	}
};

#endif /* PUK_H_ */
