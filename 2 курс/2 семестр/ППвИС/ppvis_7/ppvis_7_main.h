#ifndef _PPVIS_7_MAIN_H
#define _PPVIS_7_MAIN_H

#include <iostream>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////
template < typename T> void sort_T( int N, T * arr) {
	for(int i=0; i<N-1; i++){
		for(int j=i+1; j<N; j++){
			if(arr[i]>arr[j]){
				T temp =arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////

template < class T> class STACK {
private:
	vector  <T>	 stack;
	int			 num;
public:
	STACK(int = 5);
	void Push(const T &);
	void Pop();
	void ToShow();
	template <class A_class, int T_type> friend class ARRAY ;
};

template < class T> STACK <T> :: STACK(int _num){
	num = _num;
	stack.reserve(num);
}


template <class T> void STACK<T>::ToShow(){
	for(int i=0; i< num; i++){
		cout<<stack[i]<<" ";
	}
	cout<<endl;
}

template <class T> void STACK<T> :: Push(const T & elem){
	if(stack[num]){
		num++;
	}
	stack.push_back(elem);
}

template <class T> void STACK<T> :: Pop(){
	stack.pop_back();
	num--;
}
////////////////////////////////////////////////////////////////
template< typename A_type, typename B_type> A_type Func ( A_type a , B_type b){
	return a*b;
}

template <class A_class, int T_type> class ARRAY {
private:
	A_class     arr[T_type];
public:
	ARRAY(A_class value = 0){
		for(int i=0; i<T_type; i++){
			arr[i] = value;
		}
	}
	void ToShow(){
		cout<<"\nСодержимое массива ARRAY\n";
		for(int i=0; i<T_type; i++){
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}
};



#endif
