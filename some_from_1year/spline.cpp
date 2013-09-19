/*
 * spline.cpp
 *
 *  Created on: 30.05.2013
 *      Author: LOL
 */

/* y = arctg (x)
*	5 узлов
*	[0 , 2]		*/

/*
#include <iostream>
#include <locale.h>
using namespace std;
#include <iomanip>
#include <math.h>

float f(int i){
	float y,x;
	x = 0.5 * i;
	y = atan(x);
	return y;
}

void solve() {
	double mass[5];
	double x=0;
	cout<<"Точное решение y = arctg (x) на [0,2]:\n";
	for(int i=0; i<5 ; i++, x += 0.5) {
		mass[i] = atan(x);
		cout<<setprecision(5)<<"S("<<i*0.5<<")= "<<mass[i]<<endl;
	}
}


int mainDDD(){

	solve();

	float matr[3][3] = {
	  { 0.5333 , 0.1333 , 0      } ,
	  { 0.1333 , 0.5333 , 0.1333 } ,
	  { 0      , 0.1333 , 0.5333 }
	};

	const float h = 0.4;  // (2-0)/5 = 0.4
	float z[3]={NULL};
	for(int i=0; i<3; i++){
		z[i] = (f(i+2)-f(i+1))/h - (f(i+1)-f(i))/h;
	}

	float A[3]={NULL};
	float B[3]={NULL};
	float c[5]={NULL};
	float d[5]={NULL};
	float b[5]={NULL};
	float S[5]={NULL};

*/
	/*
	A[0] = (-matr[0][1])/matr[0][0];
	B[0] = z[0]/matr[0][0];

	A[1] = (-matr[1][2])/(matr[1][0]*A[0] + matr[1][1]);
	B[1] = (z[1]-matr[1][0]*B[0])/(matr[1][0]*A[0] + matr[1][1]);

	A[2] = 0;
	c[3] = B[2] = (z[2]-matr[2][1]*B[1])/(matr[2][1]*A[1] + matr[2][2]);
	*/
/*
	A[0] = (matr[0][1])/(-matr[0][0]);
	B[0] = -z[0]/(-matr[0][0]);

	A[1] = (matr[1][2])/(-matr[1][1] - matr[1][0]*A[0]);
	B[1] = (-z[1] + matr[1][0]*B[0])/(-matr[1][0]*A[0] - matr[1][1]);

	A[2] = 0;
	c[3] = B[2] = ( -z[2]+matr[2][1]*B[1])/(- matr[2][1]*A[1] - matr[2][2]);


	//c[2] = A[2]*c[3] + B[2];
	c[2] = A[1]*c[3] + B[1];
	c[1] = A[0]*c[2] + B[0];

	for(int i=0; i<5; i++){
		b[i] = (f(i+1)-f(i))/h - h*(c[i+1]+2*c[i])/3;
		d[i] = (c[i+1]-c[i])/(3*h);
	}


	for(int i=0; i<5; i++){
		S[i] =  b[i]*(i*h + (i+1)*h) + c[i]*pow(i*h + (i+1)*h,2) + d[i]*pow(i*h+(i+1)*h,2)+ f(i) ;
		cout<<S[i]<<endl;
	}


	return 0;
}

*/
