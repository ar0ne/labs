/*
 * Driver.cpp
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#include "driver.h"

Driver::Driver(const char * _name) {
	setName(_name);
}

Driver::~Driver() {
	delete [] name;
}

void Driver::setName(const char * _name){
	name = new char[sizeof(_name)/sizeof(char)];
	strcpy(name, _name);
}
const char * Driver::getName(void) const{
	return name;
}
