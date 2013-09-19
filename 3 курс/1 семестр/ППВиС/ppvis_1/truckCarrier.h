/*
 * truckCarrier.h
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: ar1
 */

#ifndef TRUCKCARRIER_H_
#define TRUCKCARRIER_H_

#include "ppvis_1.h"
#include "driver.h"
#include "truck.h"
#include "route.h"

class TruckCarrier: public Truck, public Driver, public Route {
private:
	char * status;
public:
	TruckCarrier(
			const char * = "green",
			const char * = "Volvo",
			int = 200, const char * = "AB 5678",
			const char * = "FREE",
			const char * = "Jessy Pinkman",
			const int = 0,
			const int = 0,
			const int = 10,
			const int = 10
			);
	virtual ~TruckCarrier();
	void setStatus(const char * );
	const char * getStatus(void) const;
	void showAllInfo(void);
};

#endif /* TRUCKCARRIER_H_ */
