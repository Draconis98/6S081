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
	if (argc < 2){
		fprintf(2, "Usage: xargs <cmd>\n");
		exit(1);
	}

	if (argc + 1 > MAXARG){
		fprintf(2,"xargs: too many arguments\n");
		exit(1);
	}

	char* paras[MAXARG];
	for (int i = 1; i < argc; i++)
		paras[i - 1] = argv[i];

	char buf[512];
	char c;
	int i = 0;
	paras[argc - 1] = buf;
	while (read(0, &c, 1)) {
		if (c == '\n'){
			paras[argc] = 0;
			buf[i++] = '\0';
			if (fork() == 0){
				exec(paras[0], paras);
				exit(0);
			}
			else {
				wait(0);
				paras[argc - 1] = buf;
				i = 0;
				
			}
		}
		else buf[i++] = c;
	}

	exit(0);

	return 0;
}
