#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#define MAX 128

int fb, fc, fd, fe, ff, fh, fi, fl, fm, fn, fo, fq, fr, fs, fv, fw, fx, fy, fA, fB, fC, fH, fL, fR, fT, fV, nof;
int mnum, Anum, Bnum, Cnum, fnum;
char pattern[MAX];

void strlwr(char *s) {
	int c = 0;
	while (s[c] != '\0') {
		if (s[c] >= 'A' && s[c] <= 'Z') {
			s[c] = s[c] + 32;
		}
		c++;
	}
}

void grep(char *file, char *origpat) {

	int fd, patlen, c = 0, x, bytes = 0, fpat = 1, nol = 0, flag = 1, m = 0, n = 0;
	char pat[MAX], ch;
	fd = open(file, O_RDONLY);
	if(fd == -1) {
		if(fs) //-s
			exit(0);
		perror("cp: Bad arguments FILE");
		exit(errno);
	}
	patlen = strlen(origpat);
	while((x = read(fd, pat, patlen))) {
		pat[patlen] = 0;
		if(pat[patlen - 1] == '\n') {
			if(fpat == 1) { //-b
				n++; //-n
				bytes = bytes + c + patlen;
			}
			c = 0;
			fpat = 1;
			lseek(fd, patlen, SEEK_CUR);
		}
		c++;
		if(fi || fy) { //-i -y
			strlwr(pat);
		}
		if(strcmp(pat, origpat) == 0) {
			if(fm) //-m
				m++;
			n++; //-n
			flag = 0; //-L -l
			nol++; // -c
			lseek(fd, -(patlen + c - 1), SEEK_CUR);
			if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o
				if(fH || (nof > 1 && fh == 0)) { //-h, -H
					printf("%s:", file);
				}
				if(fn) {
					printf("%d:", n);
				}
				if(fb) { //-b
						printf("%d:", bytes);
					}
				while(ch != '\n') {
					bytes++;
					x = read(fd, &ch, sizeof(char));
					printf("%c", ch);
				}
			}
			else {
				while(ch != '\n') {
					bytes++;
					x = read(fd, &ch, sizeof(char));
				}
			}
			c = 0;
			ch = '\0';
		}
		else {

			lseek(fd, -(patlen - 1), SEEK_CUR);
		}
		if(fm) {
			if(m == mnum) { //-m
				break;
			}
		}
	}
	if(fc) { //-c
		printf("%d\n", nol);
	}
	if(fL) { //-L
		if(flag) {
			printf("%s\n", file);
		}
	}
	if(fl) { //-l
		if(!flag) {
			printf("%s\n", file);
		}
	}
}

void listdir(char* path) {
	DIR *d;
	char str[MAX], arr[8];
	int i, len;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		if((d = opendir(path)) != NULL){
			while ((dir = readdir(d)) != NULL) {
				if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0  && strcmp(dir->d_name, "..") != 0) {
					listdir(dir->d_name);
				}
				strcpy(str, dir->d_name);
				len = strlen(str);
				for(i = 0; i < 3; i++) {
					arr[i] = str[len - 1 - i];
				}
				arr[i] = '\0';
				if(strcmp(arr, "txt") == 0) {
					printf("%s\n", str);
					grep(str, pattern);
				}
			}
			closedir(d);
		}
	}
	return;
}

int main(int argc, char *argv[]) {
	char *fnam;
	int i, c = 0, opt;
	if(argc == 2) {
		if(strcmp(argv[1], "--help") == 0) {
			printf("\nGrep Function returns the whole lines matching a specific entered pattern from given input of files prior to the options entered by the user.\nRefer to readme file for information regarding options.\nGrep stands for Global Regular Expression Print.\n\nCommand:\n./grep [Options] [Pattern] [Filenames]\n\n");
			exit(0);
		}
	}
	fb = fc = fd = fe = ff = fh = fi = fl = fm = fn = fo = fq = fr = fs = fv = fw = fx = fy = 0;
	fA = fB = fC = fH = fL = fR = fT = fV = 0;
	while((opt = getopt(argc, argv, "A:B:C:bcdef:HLhilLm:noqRrsTVvwxy")) != -1) {
		switch(opt) {
			case 'A':
				c++;
				fA = 1;
				Anum = atoi(optarg);
				break;
			case 'B':
				c++;
				fB = 1;
				Bnum = atoi(optarg);
				break;
			case 'C':
				c++;
				fC = 1;
				Cnum = atoi(optarg);
				break;
			case 'b':
				c++;
				fb = 1;
				break;
			case 'c':
				c++;
				fc = 1;
				break;
			case 'e':
				c++;
				fe = 1;
				break;
			case 'f':
				c++;
				ff = 1;
				fnam = optarg;
				break;
			case 'H':
				c++;
				fH = 1;
				break;
			case 'h':
				c++;
				fh = 1;
				break;
			case 'i':
				c++;
				fi = 1;
				break;
			case 'l':
				c++;
				fl = 1;
				break;
			case 'L':
				c++;
				fL = 1;
				break;
			case 'm':
				c = c + 2;
				mnum = atoi(optarg);
				fm = 1;
				break;
			case 'n':
				c++;
				fn = 1;
				break;
			case 'o':
				c++;
				fo = 1;
				break;
			case 'q':
				c++;
				fq = 1;
				break;
			case 'r':
				c++;
				fr = 1;
				break;
			case 'R':
				c++;
				fR = 1;
				break;
			case 's':
				c++;
				fs = 1;
				break;
			case 'T':
				c++;
				fT = 1;
				break;
			case 'V':
				c++;
				fV = 1;
				break;
			case 'v':
				c++;
				fv = 1;
				break;
			case 'w':
				c++;
				fw = 1;
				break;
			case 'x':
				c++;
				fx = 1;
				break;
			case 'y':
				c++;
				fy = 1;
				break;
			default:
				fprintf(stderr, "Usage: grep [OPTION]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
				exit(0);
		}
	}
	
	if(fq) { //-q
		exit(0);
	}
	if(fr) { //-r
		if(argc == 3) {
			listdir(".");
			exit(0);
		}
	}
	if (argc < 3) {
		if(fs) //-s
			exit(0);
		errno = EINVAL;
		perror("Bad Arguments ");
		return errno;
	}
	nof = argc - (c + 2);
	strcpy(pattern, argv[c + 1]);
	if(fi || fy) { //-i -y
		strlwr(pattern);
	}
	for(i = c + 2; i < argc; i++) {
		grep(argv[i], pattern);
	}			
	return 0;
}
