/*

 * olimp.cpp
 *
 *  Created on: 02.10.2013
 *      Author: LOL

*/

// http://olimp.bstu.by/en/problem-pid-c372?ps=1&smt=a&smpwid=0

#include <iostream>

using namespace std;

int main(){
	unsigned	int n=0,k=0,temp=0,err=0;
	bool flag=false;
	unsigned int * v;

	cin>>n>>k;
	v = new unsigned int [k];

	for(int j=0; j < k; j++){
		cin>>v[j];
	}

	int if_first = 10;

	for(int i=k,j=0; i < n; i++,j++){
		if(j==k) j=0;

		cin>>temp;

		if(temp == v[j]){
			continue;
		}else
			if(temp == if_first ){
				v[j] = if_first;
				err = j+1;
				if_first = 10;
				continue;
			}
			if(flag){
				cout<<"FAIL";
				return 0;
			}else {
				flag = true;
				err  = i+1;
				if_first = temp;

			}
	}
	cout<<"OK\n"<<err;

	return 0;
}


