
#include "circle.h"

using namespace std;

CIRCLE::CIRCLE(const char * _color, const float _radius, const int _x, const int _y) : POINT (_x, _y) {
	ToSetColor(_color);
	ToSetRadius(_radius);
}

CIRCLE::CIRCLE(const CIRCLE & obj) : POINT(obj){
	ToSetRadius(obj.radius);
	ToSetColor(obj.color);
}

void CIRCLE::ToSetColor(const char * _color){
	// new генерирует исключение bad_alloc при неудачном выполнении
	color = new char[sizeof(_color)/sizeof(char)];
	strcpy(color, _color);
}

void CIRCLE::ToSetRadius(const float _radius){
	if(_radius < 0){
		throw .0; // => double
	}
	radius = _radius;
}

void CIRCLE::ToShowCircle(void){
	cout<<"Центр круга ->";
	ToShowPoint();
	cout<<"Цвет линии: "<< color
		<<", Радиус: "<< radius
		<<", Площадь: "<< ToGetSquare() <<endl;
}

void CIRCLE::ToSetCircle(const char * _color, const float _radius, const int _x, const int _y){
	 ToSetColor (_color );
	 ToSetRadius(_radius);
	 ToSetPoint (_x, _y );
}

CIRCLE::~CIRCLE(void) {
	delete [] color;
}

float CIRCLE::ToGetSquare() const {
	return (3.14 * radius * radius);
}
