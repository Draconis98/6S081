/*************************************************************************
	> File Name:	primes.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Sun Jul 18 23:56:28 2021
 ************************************************************************/

#include "kernel/types.h"
#include "user/user.h"

const int Read = 0;
const int Write = 1;

int main(int argc, char* argv[]){
	
	if (fork() == 0){


	}
	else {

		for (int i = 2; i < 36; i++){

		}

		wait(0);	//wait until all the other primes process exited.
		exit(0);
	}
}
