/*
 * Listing chislen_integr_ar1.cpp
 * http://pastebin.com/jEqp71ZT
 */

/*
#include <iostream>
#include <locale.h>
#include <math.h>
using namespace std;
#include <iomanip>
*/
/*
1
S xe^2x dx
0

парабол(симпсона), трапеций

*/

/*

const float a = 0, b = 1, n = 5;

float f(float x){
	return x*exp(2*x);
}

float M2(){
	float x = 1;
	return 4*exp(2*x) + 4*x*exp(2*x);
}
float M4(){
	float x = 1;
	return 32*exp(2*x)+16*x*exp(2*x);
}


void Trapec() {
	float h,R2,sum=0,sum1=0;
	h = (b-a)/n;

	for(int i=1; i < n; i++) {
		sum1 += f(h*i);
	}
	sum = (sum1+(f(0)+f(h*n))/2)*h;
	cout<<"Методом трапеций : "<<sum<<endl;

	R2 = (M2()*(b-a)*pow(h,2))/12;
	cout<<" Погрешность метода составляет R2 = "<<R2<<endl;
}

void Simpson() {
	 int i;
	 float 	h = (b-a)/(2*n);
	 float sum1=0,sum2=0,sum=0,R4=0;
	 for(i=2; i < 2*n; i+=2){
		 sum1 += f(i*h);
		 sum2 += f((i-1)*h);
	 }
	 sum2 += f(9*h);

	 sum = (h*(f(0*h)+f(2*n*h)+2*sum1+4*sum2)/3);
	 cout<<"\nМетод симпсона : "<<sum<<endl;

	 R4 = M4()*(b-a)*pow(h,4)/180;
	 cout<<" Погрешность метода составляет R4 = "<<R4<<endl;
}

void exact_decision(){
	cout<<"Точное решение 2.097\n"<<endl;
}


int main() {
	exact_decision();
	Trapec();
	Simpson();
	return 0;
}

*/

