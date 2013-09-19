/*
 * driver.h
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "ppvis_1.h"

class Driver{
private:
	char * name;
	//char category;
public:
	Driver(const char * = "Jack");
	virtual ~Driver();
	void setName(const char * );
	const char * getName(void) const;
};

#endif /* DRIVER_H_ */
