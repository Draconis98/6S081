/*************************************************************************
	> File Name:	find.c
	> Author:	HanJialoong
	> email:	loonghan@foxmail.com
	> Created Time: Mon Jul 19 21:57:12 2021
 ************************************************************************/
//	Simple find. Only supports ^ . * $ operators.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int match(char*, char*);
int matchhere(char*, char*);
int matchstar(int, char*, char*);

void find(char* dir, char* filename){
	char buf[1024], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if ((fd = open(dir, 0)) < 0){
		fprintf(2, "find: cannot find %s\n", dir);
		exit(1);
	}

	if (fstat(fd, &st) < 0){
		fprintf(2, "find: cannot stat %s\n", dir);
		close(fd);
		exit(1);
	}

	if (st.type != T_DIR){
		fprintf(2, "find: %s should be a <dir>\n", dir);
		close(fd);
		exit(1);
	}

	if (strlen(dir) + 1 + DIRSIZ + 1 > sizeof buf){
		fprintf(2, "find: <dir> too long\n");
		close(fd);
		exit(1);
	}

	strcpy(buf, dir);
	p = buf + strlen(buf);
	*p++ = '/';
	while (read(fd, &de, sizeof(de)) == sizeof(de)){
		if (de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
			continue;

		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if (stat(buf, &st) < 0){
			fprintf(2, "find: cannot stat %s\n", buf);
			continue;
		}

		if (st.type == T_DIR)
			find(buf, filename);
		else if (st.type == T_FILE && match(de.name, filename))
			printf("%s\n", buf);
	}
}

int main(int argc, char* argv[]){
	if (argc < 3){
		fprintf(2, "Usage: find <dir> <filename>\n");
		exit(1);
	}

	find(argv[1], argv[2]);

	exit(0);
}

int match(char* re, char* text){
	if (re[0] == '^')
		return matchhere(re+1, text);
	do
		if (matchhere(re, text))
			return 1;
	while(*text++ != '\0');
	return 0;
}

//	matchhere: search for re at beginning of text
int matchhere(char* re, char* text){
	if (re[0] == '\0')
		return 1;
	if (re[1] == '*')
		return matchstar(re[0], re+2, text);
	if (re[0] == '$' && re[1] == '\0')
		return *text == '\0';
	if (*text != '\0' && (re[0] == '.' || re[0] == *text))
		return matchhere(re+1, text+1);
	return 0;
}

//	match star: search for c*re at beginning of text
int matchstar(int c, char* re, char* text){
	do
		if (matchhere(re, text))
			return 1;
	while(*text != '\0' && (*text++ == c || c == '.'));
	return 0;
}
