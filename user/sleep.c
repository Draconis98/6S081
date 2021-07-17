/*************************************************************************
	> File Name:	sleep.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Sat Jul 17 23:52:11 2021
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

	if (argc < 2){
		fprintf(2, "Usage: sleep <number>\n");
		exit(1);
	}

	int sec = atoi(argv[1]);
	sleep(sec);

	exit(0);
}
