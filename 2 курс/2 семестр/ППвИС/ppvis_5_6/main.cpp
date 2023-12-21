
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
		cout<< "���������� � ��������� �������� ������: \nprivate x = "<<c.ToGetX()
			<<", protected y = " << c.ToGetY()
			<<"\n������� ����� ������ ����� POINT::ToSetPoint(5,6)\n\n";
		c.ToSetPoint(5,6);
		c.ToShowCircle();

		// ������������� ������ �������� ����������
		c.ToSetRadius(-5);

	}catch (std::bad_alloc e){
		cout<<"\n��������� ������ ��������� ������: "
			<< e.what() << endl;
	}catch (double){
		cout<<"\n��������� ������ - ������� ������ ������\n";
	}

	return 0;
}
