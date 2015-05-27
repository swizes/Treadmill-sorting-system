/*
 * Puk.h
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#ifndef PUK_H_
#define PUK_H_

class Puk {

private:
	bool metal;
	bool holeOnTop;
	int size;

public:
	Puk();
	virtual ~Puk();

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
};

#endif /* PUK_H_ */
