/*
 * Car.cpp
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#include "car.h"

Car::Car(const char * _color, const char * _model) {
	setColor(_color);
	setModel(_model);
}
Car::~Car() {
	delete [] color;
	delete [] model;
}
const char *  Car::getModel() const{
	return model;
}
const char * Car::getColor() const{
	return color;
}
void Car::setModel(const char* _model){
	model = new char[sizeof(_model)/sizeof(char)];
	strcpy(model, _model);
}
void Car::setColor(const char* _color){
	color = new char[sizeof(_color)/sizeof(char)];
	strcpy(color, _color);
}
