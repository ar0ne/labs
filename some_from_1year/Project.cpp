// 12 13 2 1
/*12. Дана строка S и текстовый файл. Заменить в файле
все пустые строки на строку S.			*/

/* 9.	Дан символ C — прописная (заглавная) русская буква и текстовый файл.
 *  Создать строковый файл и записать в него все слова из исходного файла,
 *   начинающиеся на эту букву (прописную или строчную). Словом считать набор
 *   символов, не содержащий пробелов, знаков препинания и ограниченный пробелами,
 *    знаками препинания или началом/концом строки. Если исходный файл не содержит
 *     подходящих слов, то оставить результирующий файл пустым.		*/

/* 2. Даны три файла целых чисел одинакового размера. Создать
текстовый файл, содержащий эти числа, расположенные в три
столбца шириной по 20 символов (в каждом столбце содержатся
числа из соответствующего исходного файла). В начало и конец
каждой строки текстового файла добавить разделитель «|» (код 124).
Числа выравниваются по левому краю столбца.				*/

/* 1. Дан текстовый файл. Создать символьный файл,
содержащий все знаки препинания, встретившиеся в текстовом
файле (в том же порядке).								*/

/*

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAXLENGTH 2000
using namespace std;

FILE  	*NewFile( char *way ) ;
char 	*LoadFile( char *way, char *option );
void	 CLOSE(FILE *ptr,int n, char *a, ...);

long fSize=0;
////////////////////////
int main(int argc, char **argv) {
	int i,j,numS=1;
	char S[] = "OLOLO OLOLO i'm driver NLO";
	FILE *FilePtr;
	char *tempArr;
	char *mass;

/////////////////////////    first  problem   /////////////
	mass = (char*)malloc(sizeof(char)*MAXLENGTH);
	mass = LoadFile("D:/in/text1.txt" , "rt" );
	mass = (char*)realloc(mass, sizeof(char)*fSize);
	tempArr = (char*)malloc(sizeof(char)*fSize);
	FilePtr=NewFile("D:/zad1.txt");

	for(i=0,j=0; i < fSize ; i++ ,j++){
		tempArr[j]=mass[i];
		if((mass[i]=='\n') && (mass[i+1]=='\n')) {
			tempArr = (char*)realloc(tempArr , sizeof(char)*(fSize + numS*strlen(S) ) );
			j++;i++;numS++;
				for(unsigned k=0; k < strlen(S); k++,j++) {
					tempArr[j]=S[k];
				}
				tempArr[j]='\n';
		}
	}
	cout<<"1 OK\n";

	fwrite(tempArr, sizeof(char) , strlen(tempArr) ,FilePtr);
	CLOSE(FilePtr,2,mass,tempArr);


///////////////////////////		second problem	  ////////////////
	FilePtr = NewFile("D:/zad2.txt");
	mass	= (char*)malloc(sizeof(char)*MAXLENGTH);
	mass    = LoadFile ("D:/in/text2.txt", "rt");
	mass 	= (char*)realloc(mass,sizeof(char)*fSize);
	tempArr = (char*)malloc(sizeof(char)*fSize);

	char letter = argv[1][0];

	for(i = 0,j=0; i<fSize; i++){
		if(!isalpha(mass[i-1]) && ( toupper(mass[i]) == toupper(letter) )){
			while(isalpha(mass[i])) {
				tempArr[j++]=mass[i++];
			}
			tempArr[j++]=' ';
		}
	}
	tempArr[j]='\0';
	tempArr = (char*)realloc(tempArr,sizeof(char)*strlen(tempArr));

	cout<<"2 OK\n";
	fwrite(tempArr, sizeof(char) , strlen(tempArr) ,FilePtr);
	CLOSE(FilePtr,2, mass,tempArr);

/////////////////////   	third problem	//////////////

	FilePtr  = NewFile("D:/zad3.txt");
	mass	 = (char*)malloc(sizeof(char)*MAXLENGTH);
	mass     = LoadFile ("D:/in/text3.1.txt", "rt");
	mass 	 = (char*)realloc(mass,sizeof(char)*fSize);
	tempArr = (char*)malloc(sizeof(char)*(fSize*3+11*(fSize/20+1)));
	char *m2 = (char*)malloc(sizeof(char)*fSize);
	char *m3 = (char*)malloc(sizeof(char)*fSize);
	m2 = LoadFile ("D:/in/text3.2.txt", "rt");
	m3 = LoadFile ("D:/in/text3.3.txt", "rt");

	j=0;i=0;
	bool flag=false;
	int a=0;
	while(a <= (fSize*3+9*(fSize/20+1))){
		i=j*20;
		tempArr[a++]='|';
		tempArr[a++]=' ';

		for(int k=i;i<k+20 ;i++) {
			if(i < fSize){
				if(i == k && isspace(mass[i])) {
					flag=true;
					continue;
				}
				tempArr[a++]=mass[i];
			} else tempArr[a++]=' ';
		}
			if(flag){
				tempArr[a++]=' ';
				flag=false;
			}
		i=j*20;
		tempArr[a++]='|';
		tempArr[a++]=' ';
		for(int k=i;i<k+20 ;i++){
			if(i < fSize){
				if(i == k && isspace(m2[i])) {
					flag=true;
					continue;
				}
				tempArr[a++]=m2[i];
			}else tempArr[a++]=' ';
		}
			if(flag){
				tempArr[a++]=' ';
				flag=false;
			}
		i=j*20;
		tempArr[a++]='|';
		tempArr[a++]=' ';
		for(int k=i;i<k+20 ;i++){
			if(i < fSize){
				if(i == k && isspace(m3[i])) {
					flag=true;
					continue;
				}
				tempArr[a++]=m3[i];
			}else tempArr[a++]=' ';
		}
		if(flag){
			tempArr[a++]=' ';
			flag=false;
		}
		tempArr[a++]=' ';
		tempArr[a++]='|';
		tempArr[a++]='\n';

		j++;
	}
	tempArr[a]= '\0';
	cout<<"3 OK\n";

	fwrite(tempArr, sizeof(char) , strlen(tempArr) ,FilePtr);
	CLOSE(FilePtr,4,mass,tempArr,m2,m3);
	////////////////////////   four problem    ////////////
		FilePtr = NewFile("D:/zad4.txt");
		mass	= (char*)malloc(sizeof(char)*MAXLENGTH);
		mass = LoadFile ("D:/in/text4.txt", "rt");
		mass = (char*)realloc(mass,sizeof(char)*fSize);
		tempArr = (char*)malloc(sizeof(char)*fSize);

		for(i=0, j=0; i<fSize; i++ ) {
			if(!isalpha(mass[i]) && !isspace(mass[i]) && !isdigit(mass[i])){
				tempArr[j++]=mass[i];
			}
		}
		cout<<"4 OK\n";
		fwrite(tempArr, sizeof(char) , strlen(tempArr) ,FilePtr);
		CLOSE(FilePtr,2,mass,tempArr);
/////////////////////////////////
	return 0;
}
///////////////////////////////////////////////////

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

	massT = (char*)malloc(sizeof(char)*fSize);
	fread ( massT , 1  , fSize , cfPtr );
	fclose(cfPtr);
	return massT;
}

FILE *NewFile( char *way ) {
	FILE *cfPtr;
	if( (cfPtr = fopen( way , "w" )) == NULL ) {
		cout<<"File couldn't be opened\n";
		return NULL;
	}
	return cfPtr;
}

void CLOSE(FILE *ptr, int n, char *a, ...) {
	fclose(ptr);
	char **destr= &a;
	for(; n ;n--){
		free(destr++);
	}
}

*/
