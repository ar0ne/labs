
#include "main.h"

using std::cout;
using std::endl;

int main(){

	try{
		setlocale(0, "");
		POINT p1(2,3), *P_ptr;
		P_ptr = & p1;

		CIRCLE c("green" , 4 , P_ptr->ToGetX(), P_ptr->ToGetY() );
		c.ToShowCircle();
		cout<< "Обращаемся к элементам базового класса: \nprivate x = "<<c.ToGetX()
			<<", protected y = " << c.ToGetY()
			<<"\nИзменим точку центра через POINT::ToSetPoint(5,6)\n\n";
		c.ToSetPoint(5,6);
		c.ToShowCircle();

		// отрицательный радиус вызывает исключение
		c.ToSetRadius(-5);

	}catch (std::bad_alloc e){
		cout<<"\nПроизошла ошибка выделения памяти: "
			<< e.what() << endl;
	}catch (double){
		cout<<"\nПроизошла ошибка - неверно введен радиус\n";
	}

	return 0;
}
