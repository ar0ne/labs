/*
 * Route.cpp
 *
 *  Created on: 16 сент. 2014 г.
 *      Author: ar1
 */

#include "route.h"
#include "ppvis_1.h"

Route::Route(const int _x_start, const int _y_start, const int _x_finish, const int _y_finish) {
	setStart(_x_start,  _y_start);
	setFinish(_x_finish, _y_finish);
}

Route::~Route() {

}
void Route::setStart(const int _x, const int _y){
	x_start = _x;
	y_start = _y;
}
void Route::setFinish(const int _x, const int _y){
	x_finish = _x;
	y_finish = _y;
}


