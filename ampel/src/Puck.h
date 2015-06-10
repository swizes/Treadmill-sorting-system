/*
 * Puk.h
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#ifndef PUCK_H_
#define PUCK_H_

#include <iostream>

enum SIZE{OK,NOT_OK,UNKNOWN};

class Puck {

private:
	bool metal;
	bool holeOnTop;
	bool needUserInteraction;
	int size;
	SIZE sizeTyp;
	int id;
	static int idCount;

public:
	Puck();
	virtual ~Puck();
	void setPuckFromStruct(struct puckStruct);
	struct puckStruct getPuckStruct(void);
	bool isUserInteractionNeeded() const{
		return needUserInteraction;
	}

	void setUserInteractionNeeded(bool userInter){
		this->needUserInteraction = userInter;
	}

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
		std::cout << "set sizetype: " << sizeTyp << std::endl;
		this->sizeTyp = sizeTyp;
	}
};

#endif /* PUK_H_ */
