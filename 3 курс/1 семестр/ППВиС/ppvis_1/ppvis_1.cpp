//============================================================================
// Name        : ppvis_1.cpp
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ppvis_1.h"
#include "truckCarrier.h"

int main() {
	TruckCarrier tr1, tr2("Pink", "Jaguar", 30, "BB-3333", "BREAK", "Samuel", 14, 14, 56, -4);
	tr1.showAllInfo();
	tr2.showAllInfo();

	return 0;
}
