/*
 * Car.h
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#ifndef CAR_H_
#define CAR_H_

#include "ppvis_1.h"

class Car {
private:
	char * color;
	char * model;
public:
	Car(const char * = "red", const char * = "MAN");
	~Car();
	void setModel(const char*);
	void setColor(const char*);
	const char * getModel() const;
	const char * getColor() const;
};

#endif /* CAR_H_ */
