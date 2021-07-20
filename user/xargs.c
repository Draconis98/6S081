/*************************************************************************
	> File Name:	xargs.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Mon Jul 19 23:15:23 2021
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int main(int argc, char* argv[]){
	if (argc < 4){
		fprintf(2, "Usage: <cmd> | xargs <cmd>\n");
		exit(1);
	}

	if (argc + 1 > MAXARG){
		fprintf(2,"xargs: too many arguments\n");
		exit(1);
	}

	char* argvs[MAXARG];
	for (int i = 1; i < argc; i++)
		argvs[i - 1] = argv[i];
	argvs[argc] = 0;

	char buf[512];
	while (1){
		int i = 0;
		while (1){
			int len = read(0, &buf[i], 1);
			if (len == 0 || buf[i] == '\n')
				break;
			i++;
		}
		if (i == 0)
			break;

		buf[i] = 0;
		argvs[argc - 1] = buf;
		
		if (fork() == 0){
			exec(argvs[0], argvs);
			exit(0);
		}
		else {
			wait(0);
			exit(0);
		}
	}
}
