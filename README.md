#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#define MAX 128

void grep(char file[MAX], char origpat[MAX]) {

	int fd, patlen, c = 0, x, i = 0;
	char pat[128], ch;
		fd = open(file, O_RDONLY);
		if(fd == -1) {
			perror("cp: Bad arguments");
			exit(errno);
		}
		patlen = strlen(origpat);
		while((x = read(fd, pat, patlen))) {
			if(pat[patlen - 1] == '\n') {
				c = 0;
				lseek(fd, patlen, SEEK_CUR);
			}
			c++;
			if(strcmp(pat, origpat) == 0) {
				lseek(fd, -(patlen + c - 1), SEEK_CUR);
				printf("%s: ", file); 
				while(ch != '\n') {
					x = read(fd, &ch, sizeof(char));
					printf("%c", ch);
					
				}
				c = 0;
				ch = '\0';
			}
			else {
				lseek(fd, -(patlen - 1), SEEK_CUR);
			}
		}
}

int main(int argc, char *argv[]) {
	int opt;
	int flag, c, i;
	if (argc < 3) {
		errno = EINVAL;
		perror("Bad Arguments: ");
		return errno;
	}
	if ((argv[1])[0] == '-') {
		//call a fn.
	//grep(argv[2], argv[1]);
	
			
			
	return 0;
}
