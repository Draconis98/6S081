/*************************************************************************
	> File Name:	uptime.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Sat Jul 24 20:38:05 2021
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc. char* argv){
	print("%d\n", uptime());
	exit(0);
}
