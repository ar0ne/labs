#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
class CPoint{
	private:
		int
			x1,
			x2,
			ethalon;
	public:
		CPoint(){
			x1 = x2 = ethalon = 0;
		}
		 int getX1()  {
			return x1;
		}
		 int getX2()  {
			return x2;
		}
		 int getEthalon()  {
			return ethalon;
		}
		void setP(int _x1, int _x2, int _ethalon){
			x1 = _x1;
			x2 = _x2;
			ethalon = _ethalon;
		}
};

double nextW (double w, double alpha, double x, double y, double e){
	return  (w - alpha * x * (y - e));
}

double nextT ( double T, double alpha, double y, double e){
	return (T + alpha * (y - e));
}

int getY(double x1,double x2, double w1,double w2, double T){
	return (((x1*w1 + x2*w2 - T) >= 0 ) ? 1 : -1);
}

int main(){
	srand(time(NULL));
	double
		// константа, определяющая скорость (шаг) обучения (0 < alpha < 1)
		alpha = rand()%9*0.1 + 0.1,
		// весовые коэфф
		w1 = rand()%9*0.1 * (rand()%2 > 0 ? 1 : -1),
		w2 = rand()%9*0.1 * (rand()%2 > 0 ? 1 : -1),
		// пороговые значения
		T = rand()%9*0.1;

	CPoint P[4];
	P[0].setP( 1,  1, -1);
	P[1].setP(-1,  1, -1);
	P[2].setP(-1, -1, -1);
	P[3].setP( 1, -1,  1);

	// выходное значение
	int y[4];

	// процесс обучения
	do{
		for(size_t i=0; i < 4; i++){
			y[i] = getY(P[i].getX1(), P[i].getX2(), w1, w2, T );
			w1 = nextW(w1, alpha, P[i].getX1(), y[i],  P[i].getEthalon());
			w2 = nextW(w2, alpha, P[i].getX2(), y[i],  P[i].getEthalon());
			T = nextT(T, alpha, y[i], P[i].getEthalon());
		}
	} while( (getY( P[0].getX1(), P[0].getX2(), w1, w2, T ) != P[0].getEthalon() )
		|| (getY( P[1].getX1(), P[1].getX2(), w1, w2, T ) != P[1].getEthalon() )
		|| (getY( P[2].getX1(), P[2].getX2(), w1, w2, T ) != P[2].getEthalon() )
		|| (getY( P[3].getX1(), P[3].getX2(), w1, w2, T ) != P[3].getEthalon() ));

	cout<<"w1 = "<<w1<<" "<<",w2 = "<<w2<<" "<<",T = "<<T<<endl;

	int x1,x2;
	char c;

	do{
		cout<<"Введите 2 входных значения:\n" && cin>>x1>>x2;
		cout<< getY( x1, x2, w1, w2, T)<<"\nВыйти?(y)" && cin>>c;
	}while(c != 'y');

	return 0;
}