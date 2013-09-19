/*
 *   variant 5
 *   Author: ar1
 * 	 R1 : a-b divide 3 without residuals
 *	 R2 : a = 2b
 *	 relation: S5:  { (1,4) , (2,5) , (2,6) }
 *	 VxVy Q(x,y)
*/

#include <iostream>
#include <vector>
#include <ostream>
#include <iterator>

using namespace std;

void MakeMatrix(int *, const int , bool , int* );
bool Simmetric(const int * ,const int );
bool Reflex(const int *, const int );
int ** Compozition( int *, int *, const int , int **);
bool Comutativ( int *, int * , int );
int **MakeDinamycArray(int n);

/* ############################################################# */

void MakeMatrix(int *A,const int n ,bool flag , int *v ){

	for(int i=0; i<n; i++){
		cout<<endl;
		for(int j=0; j<n; j++){
			if(flag){
				if(((A[i] - A[j])%3 == 0)){
					*(v+i*n+j)= 1;
				}else {
					*(v+i*n+j) = 0;
				}
			}else //R2
				if(A[i] == 2*A[j]){
					*(v+i*n+j) = 1;
				}else {
					*(v+i*n+j) = 0;
				}
			cout<<*(v+i*n+j) <<" ";
		}
	}
}


void CheckResiduals(int *R ,const int n){

	if(Simmetric( &R[0],n ) ){
		cout<<"\n1) Отношение симметрично\n";
	}else cout<<"\n1) Отношение антисимметрично\n";

	cout<<"2) ";
	if(Reflex ( &R[0], n)){
		cout<<"Отношение рефлексивно\n";
	} else cout<<"Не рефлексивно\n";
}

bool Reflex(const int *R,const int n){

	int count=0;
	for(int i=0; i<n; i++){
		if(*(R+ i*n+i) == 0){
			count++;
			continue;
		}
		if(*(R+ i*n+i) == 1){
			continue;
		}else
			return false;
	}
	if(count == n){
		cout<<"Отношение антирефлексивно и ";
		return false;
	}
	return true;
}



bool Simmetric(const int *R ,const int n){

	for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(*(R + i*n +j) == *(R + n*j + i)){
					continue;
				}else {
					return false;
				}
			}
		}
	return true;
}

/* сложение заменяется дизъюнкцией(|), а умножение конъюнкцией.(&) */
int ** Compozition( int *R1, int *R2, const int n, int **comp){

	for(int i=0; i<n; i++) {
		cout<<endl;
		for(int j=0; j<n; j++) {
			for(int k=0; k<n; k++) {
				comp[i][j] = comp[i][j] | (*(R1+i*n+k) & *(R2+k*n+j));
			}
			cout<<comp[i][j]<<" ";
		}
	}
	return comp;
}


bool Comutativ( int *R1, int *R2 , int n){

	int **compR2R1 = MakeDinamycArray(n);
	int **compR1R2 = MakeDinamycArray(n);

	cout<<"\nКомпозиция R1*R2:\n";
	compR2R1 = Compozition(&R1[0], &R2[0], n ,compR2R1);
	cout<<"\n\nКомпозиция R2*R1:\n";
	compR1R2 = Compozition(&R2[0], &R1[0], n ,compR1R2);

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(compR2R1[i][j] != compR1R2[i][j]){
				return false;
			}
		}
	}
	return true;
}

void Uorshall(int *S, int n){

	for(int k=0,j;k<n ;k++){
		cout<<endl;
		for(int i=0;i<n;i++){
			for(j=0;j<n;j++){
				*(S+i*n+j) = *(S+i*n+j) | (*(S+i*n+k) & *(S+k*n+j));
			}
		cout<<*(S+i*n+j)<<" ";
		}
	}
}


bool Transitiv(int *R, int n){

	int **compR = MakeDinamycArray(n);

	compR = Compozition(&R[0], &R[0], n , compR);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(compR[i][j]== 1 && *(R+i*n+j)==1){
				return true;
			}
		}
	}
	return false;
}

int **MakeDinamycArray(int n){

	int **array = new int*[n];
	for(int i=0; i<n; i++){
		array[i] = new int [n];
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			array[i][j] = 0;
		}
	}
	return array;
}

void FunctionOrNOT(){
	int S[][2] = { {1,4} , {2,5} , {2,6} };
	int B[] = { 1, 2, 3 }, C[] = { 4, 5, 6 };
	cout<<"\n\n S = { {1,4} , {2,5} , {2,6} }\n A = { 1, 2, 3 }\n B = { 4, 5, 6 }\n";
	int n_size_B = sizeof(B)/sizeof(int);
	int **matrS = MakeDinamycArray(n_size_B);

	for(int i=0; i<n_size_B; i++){
		for(int j=0; j<n_size_B; j++){
			for(int k=0; k<n_size_B; k++){
				for(int l=0; l<n_size_B; l++){
					if((S[i][0] == B[k]) && (S[i][1] == C[l])){
						matrS[k][l] = 1;
					}
				}
			}
		}
	}

	for(int i=0; i<n_size_B; i++){
		cout<<endl;
		for(int j=0; j<n_size_B; j++){
			cout<<matrS[i][j]<<" ";
		}
	}
	int count;
	for(int i=0; i<n_size_B; i++){
		count = 0;
		for(int j=0; j<n_size_B; j++){
			if (matrS[i][j]==1){
				count++;
			}
		}
		if(count>1){
			cout<<"\nОтношение не является ф-цией\n";
			return ;
		}
	}
	cout<<"\nОтношение является ф-цией\n";
}

void ReverseRelation(int *R,const int n, int **v){
	for(int i=0; i<n; i++){
		cout<<endl;
		for(int j=0; j<n; j++){
			if(R[j] == 2*R[i]){
				v[i][j] = 1;
			}
			cout<<v[i][j]<<" ";
		}
	}

}

void Fields(int *R,int n,int *A){
	cout<<"\nОбласть значения D(f):\n";
	for(int i=0; i< n; i++){
		for(int j=0; j<n; j++){
			if(*(R+i*n+j)== 1){
				cout<<A[i]<<" ";
				break;
			}
		}
	}
	cout<<"\nОбласть определения E(f):\n";
	for(int i=0; i < n; i++){
		for(int j=0; j<n; j++){
			if(*(R+j*n+i)== 1){
				cout<<A[i]<<" ";
				break;
			}
		}
	}
}

void AddedMatrix(int *R, const int n){
	for(int i=0; i<n; i++){
		cout<<endl;
		for(int j=0; j<n; j++){
			if(*(R+i*n+j)==1){
				cout<<"0 ";
			}else cout<<"1 ";
		}
	}
}


int main(){

	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	const int n = sizeof(A)/sizeof(int);
	int R1[n][n],R2[n][n];
	cout<<"Матрица отношений R1:\n";
	MakeMatrix( A, n , true , &R1[0][0]);
	cout<<"\n\nМатрица отношений R2:\n";
	MakeMatrix( A, n , false, &R2[0][0] );
	cout<<"\n\nСвойства первой матрицы отношений R1:\n";
	CheckResiduals(&R1[0][0] , n);
	cout<<"\nСвойства второй матрицы отношений R2:\n";
	CheckResiduals(&R2[0][0] , n);
	if(Comutativ(&R1[0][0],&R2[0][0],n)){
		cout<<"\nВывод: Композиции коммутативны!\n";
	}else cout<<"\nВывод: Композиции не коммутативны\n";

	cout<<"\nКомпозиция R1*R1:\n";
	if(Transitiv(&R1[0][0],n)){
		cout<<"\nТранзитивна\n";
	}else {
		cout<<"\nНе транзитивна\n\nТранзитивное замыкание по алгоритму Уоршала:\n";
		Uorshall(&R1[0][0],n);
	}

	cout<<"\nКомпозиция R2*R2:\n";
	if(Transitiv(&R2[0][0],n)){
		cout<<"\nТранзитивна\n";
	}else {
		cout<<"\nНе транзитивна\n\nТранзитивное замыкание по алгоритму Уоршала:\n";
		Uorshall(&R2[0][0],n);
	}

	FunctionOrNOT();

	cout<<"\n\nДля R2:";
	Fields(&R2[0][0],n,A);
	cout<<"\n\nОбратная матрица R2:\n";
	int **reverse = MakeDinamycArray(n);
	ReverseRelation(A,n,reverse);

	cout<<"\n\nДополненная матрица R1:\n";
	AddedMatrix(&R1[0][0],n);

return 0;
}
