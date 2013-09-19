
#include "ppvis_7_main.h"

int main(){

		cout<<"Введите число элементов\n";
		int N, temp;
		cin>>N;

		STACK <int> st(N);

		// создаем массив для того чтобы его отсортировать
		int * mass = new int[N];

		for(int i=0; i<N; i++){
			cin>>temp;
			// заполняем массив и стек одними и теми числами
			mass[i] = temp;
			st.Push(temp);
		}
		cout<<"Стек содержит:\n";
		st.ToShow();

		sort_T(N,mass);

		cout<<"Массив после сортировки\n";
		for(int i=0; i<N; i++){
			// покажем отсортированный шаблонный массив
			cout<<mass[i]<<" ";
		}

		cout<<"\nСоздадим класс ARRAY из 6 элементов и по умолчанию, чем заполнить первый?\n";
		cin>>temp;

		ARRAY<double,6> arr(temp), arr_zero;
		arr.ToShow();
		arr_zero.ToShow();


	return 0;
}
