
// various 1 and 4
/*
ЗАДАЧА 1 (индивидуальное задание).

Объект автоматизации – предметная область типа “Неарифметический класс”, например, СТУДЕНТ, ГРУППА, ТОВАР, ПРАЙС, КНИГА,
 РЕЙС, МАРШРУТ и т.п.
Для заданной предметной области следует разработать класс. Он должен в итоговом варианте со-держать следующие члены.
1. 2-3 свойства-атрибута (один массивного типа).
2. Три конструктора (по одному каждого типа).
3. Методы, достаточные для установки и получения свойств объекта класса (например, TO_SET(), TO_SHOW()  и т.п.).
4. Три перегруженных оператора (операторы типа “=”, а также двуместный и одноместный операто-ры).
ЗАДАЧА 2 (индивидуальное задание).
Объект автоматизации – предметная область типа “Арифметический класс”, например, класс для обработки и хранения трех
значений целого типа;
класс для обработки и хранения одного значения вещественного и двух значений целого типа;
класс для обработки и хранения значения комплексного  типа; класс для обработки и хранения значений вектора и т.п.
Для заданной предметной области следует разработать класс аналогично ЗАДАЧЕ 2.
*/

/*
#include <iostream>
#include <locale.h>
#include <string.h>
#include <ostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <math.h>
using namespace std;

class STUDENT{
	friend ostream &operator<<(ostream &, const STUDENT &);

public:
	STUDENT(char* = "Serj", int = 10, float = 8.2);
	STUDENT(const STUDENT &);
	STUDENT(char*);
	~STUDENT();

	void TO_SHOW() const;
	STUDENT &TO_SET(char*, int,float);
	STUDENT &TO_SET_NAME(char*);
	STUDENT &TO_SET_MARK(float);
	STUDENT &TO_SET_GROUP(int);

	void operator= (const STUDENT &stud){
		name = stud.name;
		mid_mark = stud.mid_mark;
		num_group = stud.num_group;
	}

	void operator+= (const STUDENT &);

private:
	char *name;
	int num_group;
	float mid_mark;
};

STUDENT::STUDENT(char *stud_name, int group, float mark){
	num_group = group;
	mid_mark = mark;
	name = new char[strlen(stud_name)];
	strcpy(name , stud_name);
}

STUDENT::STUDENT(char * stud_name){
	num_group = 14;
	mid_mark = 5.6;
	name = new char[strlen(stud_name)];
	strcpy(name , stud_name);
}

STUDENT::STUDENT(const STUDENT &stud) : name(stud.name), mid_mark(stud.mid_mark), num_group(stud.num_group){
	cout<<"\nКонструктор копирования\n";
}

STUDENT::~STUDENT(){
	cout<<"Деструктор активирован\n";
	delete [] name;
}

void STUDENT::TO_SHOW() const{
	cout<<*this<<endl;
}

ostream &operator<<(ostream &out, const STUDENT &stud){

	out<<setw(4)<<"Имя: "<<stud.name
			<<"\nСредний балл: "<<stud.mid_mark
			<<"\nНомер группы: "<<stud.num_group<<endl;

	return out;
}

 void STUDENT::operator+= (const STUDENT &stud){

	 strcat(name,stud.name);
	 mid_mark = (mid_mark+stud.mid_mark)/2;
	 num_group = (num_group+stud.num_group)/2;
}

STUDENT &STUDENT::TO_SET(char *stud_name, int stud_group, float stud_mark){
	TO_SET_NAME(stud_name);
	TO_SET_MARK(stud_mark);
	TO_SET_GROUP(stud_group);
	return *this;
}

STUDENT &STUDENT::TO_SET_GROUP(int stud_group){
	num_group = stud_group;
	return *this;
}

STUDENT &STUDENT::TO_SET_MARK(float mark){
	mid_mark = mark;
	return *this;
}

STUDENT &STUDENT::TO_SET_NAME(char *stud_name){
	strcpy(name, stud_name);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////

class VECTOR{

	friend ostream&  operator<<(ostream &,  VECTOR &);
	friend istream&  operator>>(istream &, VECTOR &);

public:
	VECTOR();
	VECTOR( const VECTOR &);
	void TO_SHOW();
	void  TO_SET();
	VECTOR & TO_SET(int,int);
	float LENGTH();
	~VECTOR();

private:
	int x;
	int y;
};

VECTOR::VECTOR(){
	x = 0;
	y = 0;
}

VECTOR::VECTOR( const VECTOR &v ){
	x = v.x;
	y = v.y;
}

VECTOR::~VECTOR(){
	cout<<"\nДеструктор активирован!\n";
}

ostream& operator<< (ostream & out,  VECTOR & vector){
	out<<"X ="<<vector.x<<"\tY = "<<vector.y<<endl;
	return out;
}

istream& operator>> (istream & in, VECTOR & vector){
	in>>vector.x>>vector.y;
	return in;
}

float VECTOR::LENGTH(){
	cout<<"Длина вектора: \n";
	return pow(x*x + y*y, 0.5);
}


void VECTOR::TO_SHOW() {
	cout<<"\nВектор: \nX = "<<x<<"\nY = "<<y<<endl;
}

VECTOR & VECTOR::TO_SET(int X, int Y){
	x = X;
	y = Y;
	return *this;
}

void VECTOR::TO_SET(){
	cout<<"Введите значение\nX = ";			cin>>x;
	cout<<"Y = "; 							cin>>y;
}

int main(){

	STUDENT iam;
	cout<<"Первое задание:\nПредметная область - СТУДЕНТ\n"<< iam <<endl;

	STUDENT rob;
	rob.TO_SET("Robert", 12, 7.4);
	rob.TO_SHOW();

	cout<<iam.TO_SET_MARK(4.5).TO_SET_NAME("Liza").TO_SET_GROUP(45);

	iam.TO_SET("Nick",33,6.9);

	STUDENT someone(iam);
	cout<<someone<<endl;

	someone = rob;
	someone.TO_SHOW();

	iam += rob;
	cout<<iam;

	iam.~STUDENT();

	cout<<"Второе задание:\n";

	VECTOR v1, vArray[5];
	v1.TO_SHOW();

	cout<<"Введите 5 векторов: \n";
	for(int i=0; i< 5; i++){
		cout<<"vector["<<i+1<<"]\n (x,y): ";
		cin>>vArray[i];
	}
	vArray[3].TO_SET(13,5);

	for(int i=0; i<5;i++){
		cout<<vArray[i];
	}

	vArray[2].TO_SET();
	VECTOR p(v1);
	vArray[4] = p;

	for(int i=0; i<5; i++){
		cout<<endl<<i+1<<".";
		vArray[i].TO_SHOW();
		cout<<vArray[i].LENGTH();
	}


	return 0;
}

*/
