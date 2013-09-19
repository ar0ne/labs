/*
 * Truck.cpp
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#include "truck.h"

Truck::Truck(const char * _color, const char * _model, int _maxW, const char * _numGAI) : Car(_color, _model) {
	setMaxWeight(_maxW);
	setNumberGAI(_numGAI);
}
Truck::~Truck() {
	delete [] numberGAI;
}
const int Truck::getMaxWeight(void){
	return maxWeight;
}
const char * Truck::getNumberGAI() const{
	return numberGAI;
}
void Truck::setMaxWeight(int weight){
	maxWeight = weight;
}
void Truck::setNumberGAI(const char* num){
	numberGAI = new char[sizeof(num)/sizeof(char)];
	strcpy(numberGAI, num);
}

