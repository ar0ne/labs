/*
 * truck.h
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#ifndef TRUCK_H_
#define TRUCK_H_

#include "car.h"

class Truck : public Car {
private:
	int maxWeight;
	char * numberGAI;
public:
	Truck(const char * = "yellow", const char * = "BMW", int = 123, const char * = "AB 1234");
	virtual ~Truck();
	const int getMaxWeight(void);
	const char * getNumberGAI() const;
	void setMaxWeight(int);
	void setNumberGAI(const char*);
};

#endif /* TRUCK_H_ */
