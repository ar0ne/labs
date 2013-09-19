/*
 * Listing oaip_15_ar1.cpp
 *
 * 1.«Деревья»
 * 15. Вычислите среднее арифметическое всех элементов непустого дерева Т
 * и удалите все элементы меньшие этого числа. В программе используйте подпрограммы.
 * http://pastebin.com/tUGuaUpR
 */
/*
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
using namespace std;
*/

/*
struct tree{
	int data;
	tree *left;
	tree *right;
};
typedef tree *Tree;
int sum=0,N=0;

void BuildTree(int x,Tree &ptr);
void amount(int &sum,Tree ptr);
void DestroyTree(Tree &ptr, int mid);

void amount(int &sum,Tree ptr){
	if(ptr != NULL){
		amount(sum,ptr->left);
		cout<<ptr->data<<' ';
		N++;
		sum += ptr->data;
		amount(sum,ptr->right);
	}
}

void DestroyTree(Tree &ptr, int mid){
	if(ptr != NULL){
		DestroyTree(ptr->left , mid);
		DestroyTree(ptr->right,mid);
		if(ptr->data < mid){
			Tree temp ;
			temp = ptr;
			ptr = ptr->right;
			delete temp;
		}
	}
}

void BuildTree(int x,Tree &ptr){

	if(ptr == NULL){
		ptr = new tree;
		ptr->data = x;
		ptr->left=ptr->right = NULL;
	} else {
		if(x < ptr->data){
			BuildTree(x, ptr->left);
		}else if(x>ptr->data){
			BuildTree(x , ptr->right);
		}
	}
}



void FirstTask(){
	srand(time(NULL));
	int x ;
	Tree root = NULL;
	for(int i=0; i<8; i++){
		x = rand()%9 + 1;
		BuildTree( x , root );
	}
	cout<<"Задание 1.\nПорядковая выборка дерева \n";
	amount(sum,root);

	float mid = sum/N;

	cout<<"\nСреднее арифметическое: "<<mid
		<<"\nУдалили всё, что меньше средне арифметического и прошли ещё раз:\n";
	DestroyTree(root,mid);
	sum = 0;
	amount(sum,root);
}
*/

/* 2.Стек
 * 12. Дан текстовый файл. Проанализировав в программе содержимое файла, выберите из него имена и занесите
 *  в очередь. Выведите содержимое очереди на экран и посчитайте количество элементов образованной очереди.
 *  Решение в программе оформляйте через подпрограммы.
 */
/*
struct queue{
	char *data;
	queue *next;
};
typedef queue *Q;

long fSize=0;

char  *LoadFile( char *way, char *option );
void InsertQ(Q &head, Q &tail,char ptr[20]);
int PrintQ(Q ptr);

char  *LoadFile( char *way, char *option ) {
	FILE  *cfPtr;
	char *massT ;
	if( (cfPtr = fopen( way , option )) == NULL ) {
		cout<<"File not found!\n";
		return NULL;
	}
	fseek(cfPtr , 0 , SEEK_END);
	fSize = ftell(cfPtr);
	rewind(cfPtr);

	massT = new char[fSize];
	fread ( massT , 1  , fSize , cfPtr );
	fclose(cfPtr);
	return massT;
}

void InsertQ(Q &head, Q &tail,char ptr[20]){
	Q newNode = new queue;
	if(newNode != NULL){
		newNode = new queue;
		newNode->next = NULL;
		newNode->data = ptr;
		if(head == NULL){
			head = newNode;
		} else {
			tail->next = newNode;
		}
		tail = newNode;
	}
}

int PrintQ(Q ptr){
	int N=0;
	while(ptr){
		cout<<ptr->data<<"-->";
		N++;
		ptr = ptr->next;
	}
	cout<<"NULL";
	return N;
}

void SecondTask(){
	char *text = NULL;
		text = LoadFile("D:/nametext.txt","r");
		char *name[]={"Alex","Boris","Leo","Masha","David","Cris"};
		char *word;
		Q head,tail;
		head=tail=NULL;
		word = strtok(text," ");
		cout<<"\n\nЗадание 2.\n";
		int n = sizeof(name)/sizeof(char*);
		while(word){
			for(int i=0;i<n;i++){
				if(strcmp(word,name[i])==NULL){
					InsertQ(head,tail,word);
					break;
				}
			}
				word = strtok(NULL," ");
		}
		int N = PrintQ(head);
		cout<<"\nКол-во элементов: "<<N;
}
*/

/* 3. Списки
 * 8. Написать программу, содержащую процедуры формирования и просмотра списка со строковой информационной частью.
 *  Включите в нее функцию, которая оставляет в информационной части только согласные буквы находящегося там предложения.
 */
/*
struct List{
	char *data;
	List *next;
};
typedef List *list;

list AddToList(char *txt,list &ptr,list &head);
void PrintList(list ptr);
void KillAlpha(list ptr);

list AddToList(char *txt,list &ptr,list &head){
	list newNode = new List;
	newNode->data = txt;
	newNode->next = NULL;
	if(ptr == NULL){
		head = ptr = newNode;
	} else {
		ptr->next = newNode;
	}
	return newNode;
}

void PrintList(list ptr){
	while(ptr){
		cout<<ptr->data<<"-->";
		ptr = ptr->next;
	}
	cout<<"NULL\n";
}

void KillAlpha(list ptr){
	int size_str=0,i=0,k=0;
	char *temp=NULL;
	char alpha[] = {"aeqyuioAEQYUIO"};
	while(ptr){
		size_str = strlen(ptr->data);
		while(i < size_str){
			if(strchr(alpha , ptr->data[i]) == NULL) {
				temp = (char*)realloc(temp,sizeof(char)*(k+1));
				temp[k++]=ptr->data[i];
			}
			i++;
		}
		temp[k]='\0';
		k=0; i=0;
		ptr->data = temp;
		temp = (char*)malloc(sizeof(char));
		ptr = ptr->next;
	}
}

void ThirdTask(){
	list head, p;
	head = p = NULL;
	char str[] = "And you may have thought, So what? Drupal stores the base path in an array. Big whoop.";

	char *word;
	word = strtok(str , " ");
	while(word){
		p = AddToList(word,p,head);
		word = strtok(NULL," ");
	}
	cout<<"\n\nЗадание 3.\n";
	PrintList(head);
	cout<<"Уберём все гласные: \n";
	KillAlpha(head);
	PrintList(head);
}

*/

/* 4.Упорядочивание списка
 * 17. Напишите программу, которая создавала бы текстовый файл, а затем формировала список строк файла.
 *  Создайте список обратных строк. В программе используйте подпрограммы.
 */

/*
void reverse(list ptr);
list AddToListS(char *txt,list &ptr,list &head);
void FourthTask();

void reverse(list ptr){
	while(ptr){
		int size = strlen(ptr->data);
		char *temp = new char[size];
		for(int i=0,k=size-1; i < size; i++,k--){
			temp[k] = ptr->data[i];
		}
		temp[size]='\0';
		ptr->data = temp;
		ptr=ptr->next;
	}
}

list AddToListS(char *txt,list &ptr,list &head){
	list newNode = new List;
	newNode->data = new char[150];
	strcpy(newNode->data , txt);
	newNode->next = NULL;
	if(ptr == NULL){
		head = ptr = newNode;
	} else {
		ptr->next = newNode;
	}
	return newNode;
}

void FourthTask(){
	FILE *FilePtr ;
		char *word ;
		list head, p;
		head = NULL;
		p = NULL;
		if((FilePtr = fopen("D:/zad4.txt", "w"))==NULL){
			cout<<"File not found\n";
			return;
		}

		char *txtT[] = {
				"A pointer to the first occurrence in str1 of any of the characters that are part of str2,\n",
				" or a null pointer if none of the characters of str2 is found in str1 before the terminating null-character.\n",
				"If none of the characters of str2 is present in str1, a null pointer is returned.\0"
		};
		for(int i=0; i<3; i++){
			fputs(txtT[i],FilePtr);
		}

		word = new char[150];

		fclose(FilePtr);
		if((FilePtr = fopen("D:/zad4.txt", "r"))==NULL){
			cout<<"File not found\n";
			return;
		}

		for(int i=0; i<3; i++){
			fgets(word,150,FilePtr);
			p = AddToListS(word,p,head);
		}
		cout<<"\nЗадание 4.\nСписок строк файла\n";
		PrintList(head);
		reverse(head);
		cout<<"\nОбратные строки:\n";
		PrintList(head);
}

*/

/* 5. «Удаление элементов из списка»
 * 8. Написать программу, содержащую процедуру, которая формирует список М, включив в него по одному разу элементы, которые
 *  входят одновременно в оба списка М1 и М2.
 */

/*

struct ListI{
	int data;
	ListI *next;
};
typedef ListI *ls;

ls AddToListI(int x,ls &ptr,ls &head);
void PrintListI(ls ptr);
void CreateM(ls &M,ls &tM,ls &M1,ls &M2);
void FifthTask();

ls AddToListI(int x,ls &ptr,ls &head){
	ls newNode = new ListI;
	newNode->data = x;
	newNode->next = NULL;
	if(ptr == NULL){
		head = ptr = newNode;
	} else {
		ptr->next = newNode;
	}
	return newNode;
}


void PrintListI(ls ptr){
	while(ptr){
		cout<<ptr->data<<"-->";
		ptr = ptr->next;
	}
	cout<<"NULL\n";
}

void CreateM(ls &M,ls &tM,ls &M1,ls &M2){
	ls temp;
	temp = M2;
	while(M1){
		while(M2){
			if(M1->data == M2->data){
				AddToListI(M1->data ,tM,M);
			}
			M2 = M2->next;
		}
		M2 = temp;
		M1= M1->next;
	}
}

void FifthTask(){
	ls M1,M2,M,tM,tM1,tM2 ;
	M1 = M2 = M = tM = tM1 = tM2 = NULL;

	for(int i=0; i < 5; i++){
		tM1 = AddToListI(rand()%9+1,tM1,M1 );
		tM2 = AddToListI(rand()%9+1,tM2,M2 );
	}
	cout<<"\nЗадание 5.\nСоздали 2 списка M1 и M2\n";
	PrintListI(M1);
	PrintListI(M2);
	CreateM(M,tM,M1,M2);
	cout<<"Создадим список M из совпадающих эл-тов:\n";
	PrintListI(M);
}


int main(){
	setlocale(0,"");
	srand(time(NULL));
	FirstTask();
	SecondTask();
	ThirdTask();
	FourthTask();
	FifthTask();
	return 0;
}
*/


