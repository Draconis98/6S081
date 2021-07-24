/*************************************************************************
	> File Name:	primes.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Sat Jul 24 20:24:41 2021
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(int argc, char *argv[]) 
{
	    int fds[2];
	    int pid, i, res, readfd, writefd;
	    int p, n;
		if (pipe(fds)) {
	        fprintf(2, "make pipe fail\n");
	        exit(1);
		}
	    pid = fork();
		if (pid < 0) {
			fprintf(2, "fork fail\n");
			exit(1);
		} else if (pid) {// parent
			close(fds[0]); // close read
			for(i = 2;i <= 35;i++)
				write(fds[1], &i, 4);
			close(fds[1]);
			wait(0);
			exit(0);
		}// child
		while(1) {
			close(fds[1]);
			readfd = fds[0];
			res = read(readfd, &p, 4);
			if (res == 0) {
				close(readfd);
				exit(0);
			}
			if (pipe(fds)) {
				fprintf(2, "make pipe fail");
				exit(1);
			}
			pid = fork();
			if (pid < 0) {
				fprintf(2, "fork fail\n");
				exit(2);
			} else if (pid) {// parent
				writefd = fds[1];
				close(fds[0]);
				printf("prime %d\n", p);
				while(read(readfd, &n, 4)) {
					if (n % p) {
						write(writefd, &n, 4);
					}
				}
				close(readfd);
				close(writefd);
				wait(0);
				break;
			}
		}
		exit(0);
}
