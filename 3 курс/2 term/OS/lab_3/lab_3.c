#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close


/**
Вариант 6, 16. Написать программу, которая получает со стандартного потока ввода
содержимое любого текстового файла и выводит в стандартный поток вывода те его строки,
которые начинаются с цифры, заменив в этих строках все буквы X на Y. Протестировать на
различных файлах с использованием конвейеров в различных комбинациях вашей программы
и команд cat, sort, head, tail.
*/

int isNumber(char);

#define INPUT 	0
#define OUTPUT 	1

const int MAX_SIZE = 1024;

int main(void) {

	size_t block_size;
	char buf [MAX_SIZE];

	while( block_size = read( INPUT, buf, 1 ) ) {
		if ( isNumber(buf[0]) == 1) {
			write( OUTPUT , buf, block_size );
			block_size = read ( INPUT, buf, 1 );

			while( block_size != 0) {
				if( *buf == 'X' || *buf == 'x' ) {
					*buf = 'Y';
				}
				write( OUTPUT, buf, 1 );
				block_size = read( INPUT, buf, 1);

				if( *buf == '\n' ) {
					write( OUTPUT, buf, 1);
					break;
				}
			}
		}
	}
	return 0;
}

int isNumber(char letter) {
	char numbers [] = "0123456789";
	for(int i = 0; i < sizeof(numbers)/ sizeof(char); i++) {
		if(letter == numbers[i]) {
			return 1;
		}
	}
	return 0;
}