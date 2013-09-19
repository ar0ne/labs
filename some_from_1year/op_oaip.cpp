// op laba 14 - 6,27,62,75 +  var 8
//oaip   15,12,8,13,8

/*			OP				*/
/* 6.Стеки
 *
 * Дан указатель P1 на вершину стека, содержащего не менее десяти
    элементов. Извлечь из стека первые девять элементов и вывести их значе-
    ния. Вывести также адрес новой вершины стека. После извлечения элемен-
    тов из стека освобождать память, которую они занимали.
 *
 */

/*
 * Listing dinamic_struct_ar1.cpp
 * http://pastebin.com/CBK6Q5TP
 */

/*

#include <iostream>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct TNode {
	int Data;
	TNode* Next;
};

typedef  TNode *PNode;

void AddAfter(PNode P,PNode NewNode);
PNode CreateNode(PNode P);
void FirstTask();
void PrintNode(PNode ptr);
PNode Destroy(PNode head);

/////////////////////////////////////
PNode CreateNode(PNode P){
	PNode newNode = new TNode;
	newNode->Data = 1 + rand()%9;
	newNode->Next = NULL;
	AddAfter(P,newNode);
	return newNode;
}

void AddAfter(PNode P,PNode NewNode){
	NewNode->Next = P->Next;
	P->Next = NewNode;
}

void PrintNode(PNode ptr){
	if(ptr == NULL){
		cout<<"List is empty\n";
	} else {
		while(ptr != NULL){
			cout<<ptr->Data<<"-->";
			ptr = ptr->Next;
		}
		cout<<"NULL\n";
	}
}

PNode Destroy(PNode head){
	PNode temp = head;
	for(int i=0; i<9; i++){
		temp = head->Next;
		free(head);
		head=temp;
	}
	return head;
}

void FirstTask(){
	PNode P1=NULL; // head;
	PNode newNode = new TNode;
	newNode->Data = 1 + rand()%9;
	newNode->Next = NULL;
	P1 = newNode;
	for(int i=0; i < 9; i++){
		CreateNode(newNode);
	}
	cout<<"Задание 1\n";
	PrintNode(P1);
	P1 = Destroy(P1);
	PrintNode(P1);
	cout<<"Head address: "<<P1;

}

*/

/* 2.Очереди
 * Даны указатели P1 и P2 на начало и конец очереди, содержащей не
    менее пяти элементов. Используя тип TQueue (см. задание Pointer26), опи-
    сать функцию Dequeue(Q) целого типа, которая извлекает из очереди пер-
    вый (начальный) элемент, возвращает его значение и освобождает память,
    занимаемую извлеченным элементом (Q — входной и выходной параметр
    типа TQueue). С помощью функции Dequeue извлечь из исходной очереди
    пять начальных элементов и вывести их значения. Вывести также адреса
    начала и конца результирующей очереди (если очередь окажется пустой,
    то эти адреса должны быть равны nil).
 *
 */

/*
struct TQueue{
	int Data;
	struct TQueue *ptr;
};
typedef struct TQueue *QPtr;

void PrintQueue(QPtr ptr);
QPtr CreateQueue(QPtr P,int i);
void SecondTask();
QPtr Dequeue(QPtr &tail, QPtr &head);

void PrintQueue(QPtr ptr){
	if(ptr == NULL){
		cout<<"List is empty\n";
	} else {
		while(ptr != NULL){
			cout<<ptr->Data<<"-->";
			ptr = ptr->ptr;
		}
		cout<<"NULL\n";
	}
}

QPtr CreateQueue(QPtr P, int i){
	QPtr NewQ = new TQueue;
	NewQ->Data = i;// rand()%9 + 1;
	NewQ->ptr = P;
	return NewQ;
}


void SecondTask(){
	QPtr P1 = NULL;
	QPtr P2 = NULL;
	P1 = CreateQueue(P1,0);
	QPtr temp = P1;
	for(int i=0; i<4; i++){
		temp = CreateQueue(temp,i+1);
	}
	P2 = temp;
	cout<<"\n\nЗадание 2\nАдрес head: "<<P1<<"\nAдрес tail: "<<P2<<endl;
	PrintQueue(P2);

	for(int i = 0; i < 4; i++ ){
		P2 = Dequeue(P2,P1);
		PrintQueue(P2);
	}

}

QPtr Dequeue(QPtr &tail, QPtr &head){
	QPtr temp = tail;
	while(temp->ptr != head){
		temp = temp->ptr;
	}
	free(head);
	head = temp;
	head->ptr = NULL;
	return tail;
}

*/

/*
 * 3. Двусвязные списки
 * Дан непустой двусвязный список, первый, последний и текущий
    элементы которого имеют адреса P1, P2 и P3. Также даны пять чисел. Ис-
    пользуя тип TList (см. задание Задание 59), описать процедуру InsertAfter(L,
    D), которая вставляет новый элемент со значением D после текущего эле-
    мента списка L (L — входной и выходной параметр типа TList, D — вход-
    ной параметр целого типа). Вставленный элемент становится текущим. С
    помощью этой процедуры вставить пять данных чисел в исходный список
    и вывести новые адреса его первого, последнего и текущего элементов.
 *
 */

/*

struct List{
	int Data;
	List *Next;
	List *Prev;
};
typedef List *TList;

struct ptr{
	TList head,tail,cur;
}S;

typedef ptr *ss;

void ThirdTask();
TList InsertAfter(TList L, int D);
void AddFirst(TList &head, TList &tail, TList NewNode );
void CreateList(TList &head, TList &tail, TList &cur);
void PrintList(TList L);

TList InsertAfter(TList L, int D){
	TList NewNode = new List;
	NewNode->Data = D;
	NewNode->Next = L->Next;
	NewNode->Prev = L;
	L->Next = NewNode;
	NewNode->Next->Prev = NewNode;
	return NewNode;
}

void CreateList(TList &head, TList &tail, TList &cur){
	for(int i = 0; i < 5; i++){
		TList NewNode = new List;
		NewNode->Data = 15;// rand()%9+1;
		AddFirst(head,tail,NewNode);
	}
	cur = head->Next; // текущим будет 2-ой элемент
}

void AddFirst(TList &head, TList &tail, TList NewNode ){
	NewNode->Prev = NULL;
	NewNode->Next = head;
	if(head) head->Prev = NewNode;
	head = NewNode;
	if(!tail) tail = head;
}

void PrintList(TList L){
	if(L==NULL){
		cout<<"List is empty\n";
		return;
	}
	while(L != NULL){
		cout<<L->Data<<"-->";
		L = L->Next;
	}
	cout<<"NULL\n";
}

void ThirdTask(){
	S.head = S.tail = S.cur = NULL;
	int mass[5] = { 1, 2, 3, 4, 5 };
	CreateList(S.head,S.tail,S.cur);
	cout<<"\nЗадание 3\n";
	cout<<"Aдрес head: "<<S.head<<"\nАдрес tail: "<<S.tail<<"\nАдрес current: "<<S.cur<<'\n';
	PrintList(S.head);
	for(int i=0; i<5; i++){
		S.cur = InsertAfter(S.cur,mass[i]);
	}
	cout<<"\nНовые адреса:\nAдрес head: "<<S.head<<"\nАдрес tail: "<<S.tail<<"\nАдрес current: "<<S.cur<<'\n';
	PrintList(S.head);
}
*/

/*4.
 * Задание75. Даны указатели P1 и P2 на барьерный и текущий элементы двусвяз-
    ного списка. Также дано число N (> 0) и набор из N чисел. Используя тип
    TListB (см. задание Задание 74), описать процедуру LBInsertFirst(L, D), ко-
    торая добавляет новый элемент со значением D в начало списка L (L —
    входной и выходной параметр типа TListB, D — входной параметр целого
    типа). Добавленный элемент становится текущим. С помощью этой проце-
    дуры добавить в начало исходного списка данный набор чисел (добавлен-
    ные числа будут располагаться в списке в обратном порядке) и вывести
    адрес текущего элемента полученного списка.
 *
 */

/*

void FourtyTask();
TList LBInsertFirst(TList L, int D);
void PrintListB(TList ptr,TList bar);

TList LBInsertFirst(TList L, int D){
	TList NewNode = new List;
	NewNode->Data = D;
	NewNode->Next = L->Next;
	L->Next = NewNode;
	NewNode->Prev = L;
	NewNode->Next->Prev = NewNode;
	return NewNode;
}

void PrintListB(TList cur,TList bar){
	while(cur != bar){
		cout<<cur->Data<<"<--";
		cur=cur->Prev;
	}
	cout<<"barrier\n";
}

void FourtyTask(){
	TList  P1,P2;
	// P1 -> Bar, P2 -> Current
	TList Bar = new List;
	Bar->Data = 0;
	Bar->Next = Bar->Prev = Bar;
	P1=P2=Bar;
	int N = 5;
	for(int i=0; i<N;i++){
		P2 = LBInsertFirst(P2,i+1);
	}
	cout<<"\nЗадание 4\nAдрес barrier: "<<P1<<"\nАдрес current: "<<P2<<endl;
	PrintListB(P2,P1);

}

int main() {
	FirstTask();
	SecondTask();
	ThirdTask();
	FourtyTask();
	return 0;
}
*/
