/*
 * TruckCarrier.cpp
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#include "truckCarrier.h"

TruckCarrier::TruckCarrier(
		const char * _color,
		const char * _model,
		int _weight,
		const char * _number,
		const char * _status,
		const char * _name,
		const int _x_start,
		const int _y_start,
		const int _x_finish,
		const int _y_finish) :  Truck(_color, _model, _weight, _number),
								Driver(_name),
								Route(_x_start, _y_start, _x_finish, _y_finish)
{
	setStatus(_status);
}
TruckCarrier::~TruckCarrier() {
	delete [] status;
}
void TruckCarrier::setStatus(const char * _status){
	status = new char[sizeof(_status)/sizeof(char)];
	strcpy(status, _status);
}

const char * TruckCarrier::getStatus(void) const{
	return status;
}

void TruckCarrier::showAllInfo(void){
	cout<< "\nColor: " << this->getColor() <<
			"\nMax Weight: " << this->getMaxWeight() <<
			"\nModel: " << this->getModel() <<
			"\nName: " << this->getName() <<
			"\nNumber of car: " << this->getNumberGAI() <<
			"\nStatus: " << this->getStatus() << endl;
}

