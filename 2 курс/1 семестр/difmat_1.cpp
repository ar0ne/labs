/*
 * AUTOR: ar1
 * DifMat lab1.cpp
 *
 *
	На универсуме  U = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11} заданы множества A, B, C
	согласно вашему варианту (см. таблицу).

	1.	Для заданного множества  A построить булеан.
	2.	Алгоритмом «слияние» построить объединение (нечетный номер варианта) или пересечение (четный номер варианта) множеств A и B
	3.	Найти прямое произведение    и его мощность.
*/

// вариант 5:
// A{1,3,4,7}	B{3,5,6,7,8}	C{2,4,5,7}	  A^(B\C)
//

/*
#include <iostream>
#include <vector>
#include <ostream>
#include <iterator>
#include <list>
#include <cmath>
#include <algorithm>
//#include <utility>

using namespace std;

void BuildBool(int *, int *, int);
vector<int> to_byte(int , unsigned int);
void BuildUnion(int *, int *, int, int);
void Multiply( int * , int *, int, int);
/////////////////////////////////////////////////////

vector<int> to_byte(int k , unsigned int size){
	vector<int>s;
		while(k != 0){
			s.push_back(k%2 == 1 ? 1 : 0 ) ;
			k /= 2;
		}
		//добавляю 0 где недостаточно их и реверсирую
		while(s.size() !=  size)  s.push_back(0);

		reverse(s.begin(),s.end());
	return s;
}

void BuildBool(int *A, int *B, int A_size){

		vector <int> v (A, A + A_size);
		vector <int> s;

		int n = pow(2,v.size());

		cout<<"Множество A: ";
		copy(v.begin() , v.end(), ostream_iterator<int>(cout, " "));
		cout<<"\nБулеан A:\n";

		for( int i=0; i < n ; i++){
			s = to_byte(i,A_size);
			for(int j=0; j != A_size; j++){
				if(s[j]==1) cout<<v[j]<<" ";
			}
			cout<<endl;
		}
}


void BuildUnion(int *A, int *B, int A_size, int B_size){

	list <int> A_list(A,A+A_size);
	list <int> B_list(B,B+B_size);
	list <int> united_list;
	list <int>::iterator pos;

	cout<<"\nПостроить объединение из:\nA: ";
	for(pos = A_list.begin(); pos != A_list.end(); ++pos){
		cout<< *pos <<" ";
	}
	cout<<"\nB: ";
	for(pos = B_list.begin(); pos != B_list.end(); ++pos){
		cout<< *pos <<" ";
	}
	cout<<endl;

	while(!A_list.empty() || !B_list.empty()){
		if(A_list.front() > B_list.front() ){
			united_list.push_back(B_list.front());
			B_list.pop_front();
		} else if (A_list.front() < B_list.front()) {
			united_list.push_back(A_list.front()) ;
			A_list.pop_front();
		} else {
			united_list.push_back(A_list.front()) ;
			A_list.pop_front();
			B_list.pop_front();
		}
	}
	if(!A_list.empty()){
		while(!A_list.empty())
		united_list.push_back(A_list.front());
		A_list.pop_front();
	}
	if(!B_list.empty()){
			while(!B_list.empty())
			united_list.push_back(B_list.front());
			B_list.pop_front();
	}

	cout<<"Объединение A u B:\n";
	for(pos = united_list.begin(); pos != united_list.end(); pos++){
		cout<< *pos <<" ";
	}

}

void Multiply( int *A ,  int *B , int A_size, int B_size){

	vector< pair <int,int> > M(A_size*B_size);
	 vector<pair <int,int> >::iterator pos;

	int k=0;
	for(int i=0; i != A_size; i++){
		for(int j=0; j != B_size; j++){
			M[k].first = A[i];
			M[k].second = B[j];
			k++;
		}
	}

	cout<<"\n\nПрямое произведение |AxB| = "<<A_size*B_size<<endl;
	for(pos = M.begin(); pos!= M.end(); pos++){
		cout<<pos->first<<","<<pos->second<<"  ";
	}

}
*/

/////////////////////////////////////////////////////

/*
int main(){
	 int A[] = {1,3,4,7};
	 int B[] = {3,5,6,7,8};
	 int A_size = sizeof(A)/sizeof(int);
	 int B_size = sizeof(B)/sizeof(int);

	 BuildBool(A,B,A_size);
	 BuildUnion(A,B,A_size,B_size);
	 Multiply(A,B,A_size,B_size);

return 0;
}

*/

