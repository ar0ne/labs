/*
 * Route.h
 *
 *  Created on: 16 сент. 2014 г.
 *      Author: ar1
 */

#ifndef ROUTE_H_
#define ROUTE_H_

class Route {
private:
	int x_start; // начальные координаты
	int y_start;
	int x_finish; // конец маршрута
	int y_finish;
public:
	Route(  const int = 1,
			const int = 2,
			const int = 3,
			const int = 4);
	virtual ~Route();
	void setStart(const int, const int);
	void setFinish(const int, const int);
};

#endif /* ROUTE_H_ */
