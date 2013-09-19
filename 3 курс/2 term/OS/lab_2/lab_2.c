/*
 ============================================================================
 Name        : lab_2.c
 Author      : ar1
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


/**
 * Написать программу, которая будет реализовывать следующие функции:
•
сразу после запуска получает и сообщает свой ID и ID родительского
процесса;
•
перед каждым выводом сообщения об ID процесса и родительского
процесса эта информация получается заново;
•
порождает процессы, формируя генеалогическое дерево согласно варианту,
сообщая, что "процесс с ID таким-то породил процесс с таким-то ID";
•
перед завершением процесса сообщить, что "процесс с таким-то ID и таким-
то ID родителя завершает работу";
•
один из процессов должен вместо себя запустить программу, указанную в
варианте задания.

var 6
fork: 	0 1 1 2 4 4 4
		1 2 3 4 5 6 7

exec:	6		ls

execl("/bin/ls", "ls", "-la", (char *)0);

 *
 */

void getInfo();


int main(int argc, char *argv[]) {
	getInfo(1);

	pid_t pid;

	if((pid = fork()) == -1) {
		printf("Failed fork process (2)");
		exit(1);
	} else if (pid == 0) { // child process
		getInfo(2);

		if((pid = fork()) == -1) {
			printf("Failed fork process (4)");
		} else if(pid == 0) { // child

			getInfo(4);

			if((pid = fork()) == -1) {
				printf("Failed fork process (5)");
			} else if( pid == 0 ) { // child
				getInfo(5);
				printf("End ");
				getInfo(5);
				exit(0);
			}

			if((pid = fork()) == -1) {
				printf("Failed fork process (6)");
			} else if( pid == 0 ) { // child
				getInfo(6);

				printf("\nThe 6th process exec: $ ls -la\n");
				execl("/bin/ls", "ls", "-la", (char *)0);

				printf("End ");
				getInfo(6);
				exit(0);
			} else { // parent

			}

			if((pid = fork()) == -1) {
				printf("Failed fork process (7)");
			} else if( pid == 0 ) { // child
				getInfo(7);
				printf("End ");
				getInfo(7);
				exit(0);
			}

			sleep(1);
			printf("End ");
			getInfo(4);
			exit(0);
		}

		sleep(2);
		printf("End ");
		getInfo(2);
		exit(0);

	} else { // parent
		if((pid = fork()) == -1) {
			printf("Failed fork process (3)");
			exit(1);
		} else if (pid == 0) { // child process
			getInfo(3);
			printf("End ");
			getInfo(3);
			exit(0);
		}
	}


	sleep(3);
	printf("End ");
	getInfo(1);

	return 0;
}

void getInfo(int num){
	printf("Process %d:\tPID: %5d,\tPPID: %5d\n" , num, getpid(), getppid() );
}

