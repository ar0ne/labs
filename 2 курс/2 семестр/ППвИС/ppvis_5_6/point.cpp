
#include "point.h"
#include "main.h"

using std::cout;
using std::endl;

POINT_NAMESPACE::POINT::POINT(const int _x, const int _y){
	ToSetPoint(_x, _y);
}

POINT_NAMESPACE::POINT::POINT(const POINT & obj) {
	ToSetPoint(obj.x, obj.y);
}

void POINT_NAMESPACE::POINT::ToShowPoint(void) const{
	cout <<"["<<x<<" , "<<y<<"]"<<endl;
}

void POINT_NAMESPACE::POINT::ToSetPoint(const int _x, const int _y) {
	x = _x;
	y = _y;
}

int POINT_NAMESPACE::POINT::ToGetX(void) const {
	return x;
}

int POINT_NAMESPACE::POINT::ToGetY(void) const {
	return y;
}
