/*************************************************************************
	> File Name:	pingpong.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Sun Jul 18 21:45:43 2021
 ************************************************************************/

#include "kernel/tpyes.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
	int parent_to_child[2];
	int child_to_parent[2];

	pipe(parent_to_child);
	pipe(child_to_parent);

	char c;

	if (fork() == 0){	//child 
		close(parent_to_child[1]);
		close(child_to_parent[0]);
		
		if (read(parent_to_child[0], &c, 1) != 1){
			fprintf(2, "child read error\n");
			exit(1);
		}

		printf("%d: received ping\n", getpid());
		write(child_to_parent[1], &c, 1);

		close(parent_to_child[0]);
		close(child_to_parent[1]);

		exit(0);
	}
	else {	//parent 
		close(parent_to_child[0]);
		close(child_to_parent[1]);

		write(parent_to_child[1], &c, 1);

		if (read(child_to_parent[0], &c, 1) != 1){
			fprintf(2, "parent read error\n");
			exit(1);
		}
		
		printf("%d: received pong\n", getpid());

		close(parent_to_child[1]);
		close(child_to_parent[0]);

		wait(0);

		exit(0);
	}
}
