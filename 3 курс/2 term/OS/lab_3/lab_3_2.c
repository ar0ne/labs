#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define INPUT 	0
#define OUTPUT 	1

const int MAX_SIZE = 1024;

int isNumber(char);

/**
const int buf_size=500;

int main()
{
	char buf1[buf_size];
	char buf2[buf_size];
	char vowels[]="0123456789";
	int  size;
	int  i, b;
	char ch[]="Y\0";

	while(size=read(0,buf1,1))
	{
		b=0;
		i=0;
		*buf2=*buf1;
		
		if(strchr(vowels, buf1[0])!=NULL)
			b=1;
		
		while(*buf1!='\n' && size!=0)
		{
			if(b)
			{
				if(*buf1=='X')
					write(1,ch,1);
				else
					write(1,buf1,1);
			}
			size=read(0,buf1,1);
			i++;
			if(size)
				*(buf2+i)=*buf1;
		}
		
		i++;
		*(buf2+i)='\0';
		*buf1='\n';
		write(1,buf1,1);
		write(2,buf2,strlen(buf2));
	}
	return 0;
}
*/

int main(void) {

	size_t block_size;
	char buf [MAX_SIZE];
	int fd;
	char ch;
	ssize_t ret;

	if( (fd = open("myfile", O_RDONLY ) ) < 0){
		printf("Can\'t open file\n");
		exit(-1);
	}
/*
	переменная = 1

	продолжаем пока есть что считывать

		если переменная == 1 и есть что считать с файла
			считать строку с файла
				проверить - если с цифры
							вывести изменяя
						иначе
							переключаемся на консоль
		иначе если переменная == 2  и есть что считать с консоли
			считать с консоли
				проверить - если с цифры
							вывести изменяя
						иначе
							переключаемся на считать с файла
		иначе выход
*/

	int cur = 1;

	while ( 1 ) {
 
		if( (ret = read (fd, &ch, 1) ) > 0  && cur == 1 ) {

			if ( isNumber(ch) == 1 ) {
				write( OUTPUT , &ch, 1 );
				ret = read ( fd, &ch, 1 );

				while( ret != 0 ) {
					if( ch == 'X' || ch == 'x' ) {
						ch = 'Y';
					}
					write( OUTPUT, &ch, 1 );
					ret = read( fd, &ch, 1);

					if( ch == '\n' ) {
						write( OUTPUT, &ch, 1);
						cur = 2;
						break;
					}
				}
			} else {
				cur = 2;
			}

		} 

	    if( block_size = read( INPUT, buf, 1 ) && cur == 2 ) {

			if ( isNumber(buf[0]) == 1 ) {
				write( OUTPUT , buf, 1 );
				block_size = read ( INPUT, buf, 1 );

				while( block_size != 0 ) {
					if( *buf == 'X' || *buf == 'x' ) {
						*buf = 'Y';
					}
					write( OUTPUT, buf, 1 );
					block_size = read( INPUT, buf, 1);

					if( *buf == '\n' ) {
						write( OUTPUT, buf, 1);
						cur = 1;
						break;
					}
				}
			} else {
				block_size = read( INPUT, buf, 1);
				while(*buf == '\n' ){
					block_size = read( INPUT, buf, 1);
				}
				cur = 1;
			}
		}

		if(ret == 0 && block_size == 0) {
			break;
		}
	}

	if(close(fd) < 0){
		printf("Can\'t close file\n");
	}

	write( OUTPUT, "\n", 1 );



	return 0;
}

int isNumber(char letter) {
	char numbers [] = "0123456789";
	int length = sizeof(numbers) / sizeof(char);
	for(int i = 0; i < length; i++) {
		if(letter == numbers[i]) {
			return 1;
		}
	}
	return 0;
}

void readFromFile(int fd){
	//char ch;

}


// int fd;
// size_t size;
// char string[] = "Hello, world!";
// /* Обнуляем маску создания файлов текущего процесса для того,
// чтобы права доступа у создаваемого файла точно соответствовали
// чпараметру вызова open() */
// (void)umask(0);
//  Попытаемся открыть файл с именем myfile в текущей директории
// только для операций вывода. Если файла не существует, попробуем
// его создать с правами доступа 0666, т. е. read-write для всех
// категорий пользователей 
// if((fd = open("myfile", O_WRONLY | O_CREAT,
// 0666)) < 0){
// /* Если файл открыть не удалось, печатаем об этом сообщение
// и прекращаем работу */
// printf("Can\'t open file\n");
// exit(-1);
// }
// /* Пробуем записать в файл 14 байт из нашего массива, т.е. всю
// строку "Hello, world!" вместе с признаком конца
// строки */
// size = write(fd, string, 14);
// if(size != 14){

// /* Если записалось меньшее количество байт, сообщаем об
// ошибке */
// printf("Can\'t write all string\n");
// exit(-1);
// }
// /* Закрываем файл */
// if(close(fd) < 0){
// printf("Can\'t close file\n");
// }
