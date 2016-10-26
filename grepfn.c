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
	int visited[1024], fd, i, patlen, c = 0, x, bytes = 0, nol = 0, flag = 1, m = 0, n = 0, flagA = 0, a = 0, cn = 1, byt;
	int flagB;
	char pat[MAX], ch;
	fd = open(file, O_RDONLY);
	if(fd == -1) {
		if(fs) //-s
			exit(0);
		printf("./grep: %s: No such file or directory\n", file);
		exit(errno);
	}
	for(i = 0; i < 1024; i++) {
		visited[i] = 0;
	}
	patlen = strlen(origpat);
	while((x = read(fd, pat, patlen))) {
		pat[patlen] = 0;
		c++;
		if(pat[patlen - 1] == '\n') {
			n++; //-n
			if(fA) {
				if(flagA) {
					if(Anum != a) {
						lseek(fd, -(patlen + c), SEEK_CUR);
						if(fH || (nof > 1 && fh == 0)) { //-h, -H
							if(!fT) { //-T
								printf("%s-", file);
							}
							else {
								printf("%s-	", file);
							}
						}
						if(fn) { //-n
							if(!fT) { // -T
								printf("%d-", n);
							}
							else {
								printf("%d-	", n);
							}
						}
						if(fb) { //-b
							if(!fT) { //-T
								printf("%d-", bytes);
							}
							else {
								printf("%d-	", bytes);
							}
						}
						while(ch != '\n') {
							x = read(fd, &ch, sizeof(char));
							printf("%c", ch);
						}
						a++;
						ch = '\0';
					}
					else {
						printf("--\n");
						a = 0;
						flagA = 0;
					}
				}
			}
			bytes = bytes + c + patlen - 1;
			c = 0;
			lseek(fd, patlen - 1, SEEK_CUR);
		}
		if(fi || fy) { //-i -y
			strlwr(pat);
		}
		if(strcmp(pat, origpat) == 0) {
			flagB = 0;
			if(fA) {
				flagA = 1;
				a = 0;
			}
			if(fm) //-m
				m++;
			n++; //-n
			flag = 0; //-L -l
			nol++; // -c
			visited[n] = 1;
			byt = lseek(fd, -(patlen + c - 1), SEEK_CUR);
			if(fB) {
				if(byt > 1) {
					byt = lseek(fd, -2, SEEK_CUR);
					while(cn <= Bnum && (visited[n - cn] != 1) && byt > 1) {
						x = read(fd, &ch, sizeof(char));
						if(ch == '\n') {
							cn++;
						}
						if(byt > 1) {
							byt = lseek(fd, -2, SEEK_CUR);
						}
						if(byt == 1) {
							byt = lseek(fd, -1, SEEK_CUR);
							cn++;
						}
					}
					if(byt > 1){
						byt = lseek(fd, 2, SEEK_CUR);
					}
					if(fH || (nof > 1 && fh == 0)) { //-h, -H
						if(!fT) { //-T
							printf("%s-", file);
						}
						else {
							printf("%s-	", file);
						}
					}
					if(fn) { //-n
						if(!fT) { // -T
							printf("%d-", n - cn + 1);
						}
						else {
							printf("%d-	", n - cn + 1);
						}
					}
					if(fb) { //-b
						if(!fT) { //-T
							printf("%d-", bytes);
						}
						else {
							printf("%d-	", bytes);
						}
					}
					while(cn > 0) {
						x = read(fd, &ch, sizeof(char));
						printf("%c", ch);
						if(ch == '\n') {
							cn--;
							if(cn > 0) {
								if(fH || (nof > 1 && fh == 0)) { //-h, -H
									if(!fT) { //-T
										if(cn == 1) {
											printf("%s:", file);
										}
										else {
											printf("%s-", file);
										}
										flagB = 1;
									}
									else {
										if(cn == 1) {
											printf("%s:	", file);
										}
										else {
											printf("%s-	", file);
										}
										flagB = 1;
									}
								}
								if(fn) { //-n
									if(!fT) { // -T
										if(cn == 1) {
											printf("%d:", n - cn +1);
										}
										else {
											printf("%d-", n - cn +1);
										}
										flagB = 1;
									}
									else {
										if(cn == 1) {
											printf("%d:	", n - cn +1);
										}
										else {
											printf("%d-	", n - cn +1);
										}
										flagB = 1;
									}
								}
								if(fb) { //-b
									if(!fT) { //-T
										if(cn == 1) {
											printf("%d:", bytes);
										}
										else {
											printf("%d-", bytes);
										}
										flagB = 1;
									}
									else {
										if(cn == 1) {
											printf("%d:	", bytes);
										}
										else {
											printf("%d-	", bytes);
										}
										flagB = 1;
									}
								}
							}
						}
					}
					cn = 1;
				}
			}		
			if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
				if(fH || (nof > 1 && fh == 0)) { //-h, -H
					if(!fT && !flagB) { //-T
						printf("%s:", file);
					}
					else if(!flagB){
						printf("%s:	", file);
					}
				}
				if(fn && !flagB) { //-n
					if(!fT) { // -T
						printf("%d:", n);
					}
					else {
						printf("%d:	", n);
					}
				}
				if(fb && !flagB) { //-b
					if(!fT) { //-T
						printf("%d:", bytes);
					}
					else {
						printf("%d:	", bytes);
					}
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
void grepv(char *file, char *origpat) {

	int visited[1024], fd, i = 0, patlen, c = 0, x, bytes = 0, nol = 0, flag = 1, m = 0, n = 0, flagA = 0, a = 0, cn = 1;
	int byt;
	int flagB;
	char pat[MAX], ch;
	fd = open(file, O_RDONLY);
	if(fd == -1) {
		if(fs) //-s
			exit(0);
		printf("./grep: %s: No such file or directory\n", file);
		exit(errno);
	}
	for(i = 0; i < 1024; i++) {
		visited[i] = 0;
	}
	patlen = strlen(origpat);
	while((x = read(fd, pat, patlen))) {
		c++;
		pat[patlen] = 0;
		if(fi || fy) { //-i -y
			strlwr(pat);
		}
		if(pat[patlen - 1] == '\n') {
			flag = 0;
			nol++;
			n++;
			if(fm) {
				m++;
			}
			lseek(fd, -(patlen + c - 1), SEEK_CUR);
			if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
				if(fH || (nof > 1 && fh == 0)) { //-h, -H
					if(!fT && !flagB) { //-T
						printf("%s:", file);
					}
					else if(!flagB){
						printf("%s:	", file);
					}
				}
				if(fn && !flagB) { //-n
					if(!fT) { // -T
						printf("%d:", n);
					}
					else {
						printf("%d:	", n);
					}
				}
				if(fb && !flagB) { //-b
					if(!fT) { //-T
						printf("%d:", bytes);
					}
					else {
						printf("%d:	", bytes);
					}
				}
			}	
			while(ch != '\n') {
				bytes++;
				x = read(fd, &ch, sizeof(char));
				if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
					printf("%c", ch);
				}
			}
				ch = '\0';
			if(fA) {
				if(flagA) {
					if(Anum != a) {
						if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
							
							if(fH || (nof > 1 && fh == 0)) { //-h, -H
								if(!fT) { //-T
									printf("%s-", file);
								}
								else {
									printf("%s-	", file);
								}
							}
							if(fn) { //-n
								if(!fT) { // -T
									printf("%d-", n);
								}
								else {
									printf("%d-	", n);
								}
							}
							if(fb) { //-b
								if(!fT) { //-T
									printf("%d-", bytes);
								}
								else {
									printf("%d-	", bytes);
								}
							}
							while(ch != '\n') {
								x = read(fd, &ch, sizeof(char));
								printf("%c", ch);
							}
							a++;
							ch = '\0';
						}
					}	
					else {
						printf("--\n");
						a = 0;
						flagA = 0;
					}
				}
			}
			c = 0;
			ch = '\0';
		}
		else if(strcmp(pat, origpat) == 0) {		
			flagA = 1;
			lseek(fd, -(patlen + c - 1), SEEK_CUR);
			while(ch != '\n') {
				x = read(fd, &ch, sizeof(char));
				bytes++;
			}
			c = 0;
			ch = '\0';
			n++;
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
void grepx(char *file, char *origpat) {
	int visited[1024], fd, i, patlen, c = 0, x = 1, bytes = 0, nol = 0, flag = 1, m = 0, n = 0, flagA = 0, a = 0, cn = 1;
	int flagB, len;
	char pat[MAX], ch, string[MAX], PAttern[MAX];
	fd = open(file, O_RDONLY);
	if(fd == -1) {
		if(fs) //-s
			exit(0);
		printf("./grep: %s: No such file or directory\n", file);
		exit(errno);
	}
	for(i = 0; i < 1024; i++) {
		visited[i] = 0;
	}
	patlen = strlen(origpat);
	while(x) {
		pat[patlen] = 0;
		len = 0;
		while((ch != '\n') && x) {
			x = read(fd, &ch, sizeof(char));
			len++;
		}
		ch = '\0';
		if(patlen == (len - 1)) {
			n++;
			nol++;
			flag = 0;
			lseek(fd, -(patlen + 1), SEEK_CUR);
			x = read(fd, pat, patlen);
			strcpy(PAttern, pat);
			if(fi || fy) { //-i -y
				strlwr(pat);
			}
			if(strcmp(pat, origpat) == 0) {
				m++;
				if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
					if(fH || (nof > 1 && fh == 0)) { //-h, -H
						if(!fT) { //-T
							printf("%s:", file);
						}
						else {
							printf("%s:	", file);
						}
					}
					if(fn) { //-n
						if(!fT) { // -T
							printf("%d:", n);
						}
					else {
							printf("%d:	", n);
						}
					}
					if(fb) { //-b
						if(!fT) { //-T
							printf("%d:", bytes);
						}
						else {
							printf("%d:	", bytes);
						}
					}
				
					printf("%s", PAttern);
				}
				read(fd, &ch, sizeof(char));
				if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
					printf("%c", ch);
					bytes = bytes + patlen + 1;
				}
			}
			if(fA) {
				flagA = 1;
				a = 0;
			}
		}
		else {
			
			n++;
			if(fA) {
				if(flagA) {
					if(Anum != a) {
						ch = '\0';
						lseek(fd, -len, SEEK_CUR);
						if(fH || (nof > 1 && fh == 0)) { //-h, -H
							if(!fT) { //-T
								printf("%s-", file);
							}
							else {
								printf("%s-	", file);
							}
						}
						if(fn) { //-n
							if(!fT) { // -T
								printf("%d-", n);
							}
							else {
								printf("%d-	", n);
							}
						}
						if(fb) { //-b
							if(!fT) { //-T
								printf("%d-", bytes);
							}
							else {
								printf("%d-	", bytes);
							}
						}
						while(ch != '\n') {
							read(fd, &ch, sizeof(char));
							printf("%c", ch);
						}
						a++;
					}
					else {
						printf("--\n");
						a = 0;
						flagA = 0;
					}
				}
			}
			bytes += len;
		}
		ch = '\0';
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

void grepw(char *file, char *origpat) {
	int visited[1024], fd, i, patlen, c = 0, x, bytes = 0, nol = 0, flag = 1, m = 0, n = 0, flagA = 0, a = 0, cn = 1, byt;
	int flagB, y;
	char pat[MAX], ch, nch, pch;
	fd = open(file, O_RDONLY);
	if(fd == -1) {
		if(fs) //-s
			exit(0);
		printf("./grep: %s: No such file or directory\n", file);
		exit(errno);
	}
	for(i = 0; i < 1024; i++) {
		visited[i] = 0;
	}
	patlen = strlen(origpat);
	while((x = read(fd, pat, patlen))) {
		pat[patlen] = 0;
		c++;
		if(pat[patlen - 1] == '\n') {
			n++; //-n
			if(fA) {
				if(flagA) {
					if(Anum != a) {
						lseek(fd, -(patlen + c), SEEK_CUR);
						if(fH || (nof > 1 && fh == 0)) { //-h, -H
							if(!fT) { //-T
								printf("%s-", file);
							}
							else {
								printf("%s	-", file);
							}
						}
						if(fn) { //-n
							if(!fT) { // -T
								printf("%d-", n);
							}
							else {
								printf("%d	-", n);
							}
						}
						if(fb) { //-b
							if(!fT) { //-T
								printf("%d-", bytes);
							}
							else {
								printf("%d	-", bytes);
							}
						}
						while(ch != '\n') {
							x = read(fd, &ch, sizeof(char));
							printf("%c", ch);
						}
						a++;
						ch = '\0';
					}
					else {
						printf("--\n");
						a = 0;
						flagA = 0;
					}
				}
			}
			bytes = bytes + c + patlen - 1;
			c = 0;
			lseek(fd, patlen - 1, SEEK_CUR);
		}
		if(fi || fy) { //-i -y
			strlwr(pat);
		}
		if(strcmp(pat, origpat) == 0) {
			flagB = 0;
			if(fA) {
				flagA = 1;
				a = 0;
			}
			if(fm) //-m
				m++;
			flag = 0; //-L -l
			nol++; // -c
			visited[n] = 1;
			y = read(fd, &nch, 1);
			lseek(fd, -1, SEEK_CUR);
			n++; //-n
			byt = lseek(fd, -(patlen + c - 1), SEEK_CUR);
			if(!isalnum(pch) && !isalnum(nch)) {		
				if(!fc && !fL && !fl && !fo) { // -c, -L, -l -o.....No lines printed for these options
					if(fH || (nof > 1 && fh == 0)) { //-h, -H
						if(!fT && !flagB) { //-T
							printf("%s:", file);
						}
						else if(!flagB){
							printf("%s:	", file);
						}
					}
					if(fn && !flagB) { //-n
						if(!fT) { // -T
							printf("%d:", n);
						}
						else {
							printf("%d:	", n);
						}
					}
					if(fb && !flagB) { //-b
						if(!fT) { //-T
							printf("%d:", bytes);
						}
						else {
							printf("%d:	", bytes);
						}
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
		pch = pat[0];
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

void listdir(char* path, int n) { //-r -R
	DIR *d;
	char str[MAX], arr[8], cwd[512];
	int i, len;
	struct dirent *dir;
	d = opendir(".");
	if(d) {
		if((d = opendir(path)) != NULL){
			while ((dir = readdir(d)) != NULL) {
				if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0  && strcmp(dir->d_name, "..") != 0) {
					listdir(dir->d_name, 1);
				}
				strcpy(str, dir->d_name);
				len = strlen(str);
				for(i = 0; i < 3; i++) {
					arr[i] = str[len - 1 - i];
				}
				arr[i] = '\0';
				if(strcmp(arr, "txt") == 0) {
					//printf("%s\n", str);
					if(n) {
						strcat(path, "/");
						strcat(path, str);						
					}
					else {
						if(fv) {
							grepv(str, pattern);
						}
						else if(fx) {
							grepx(str, pattern);
						}
						else {
							grep(str, pattern);
						}
					}
				}
			}
			closedir(d);
		}
	}
	return;
}

int main(int argc, char *argv[]) {
	char *fnam, ch;
	int i, c = 0, x = 1, opt, len = 0, a = 0;
	if(argc == 2) {
		if(strcmp(argv[1], "--help") == 0) {
			printf("\nGrep Function returns the whole lines matching a specific entered pattern from given input of files prior to the options entered by the user.\nRefer to readme file for information regarding options.\nGrep stands for Global Regular Expression Print.\n\nCommand:\n./grep [Options] [Pattern] [Filenames]\n\n");
			exit(0);
		}
	}
	fb = fc = fd = fe = ff = fh = fi = fl = fm = fn = fo = fq = fr = fs = fv = fw = fx = fy = 0;
	fA = fB = fC = fH = fL = fR = fT = fV = 0;
	while((opt = getopt(argc, argv, "A:B:C:bcdf:HLhilLm:noqRrsTVvwxy")) != -1) {
		switch(opt) {
			case 'A':
				c += 2;
				fA = 1;
				Anum = atoi(optarg);
				break;
			case 'B':
				c += 2;
				fB = 1;
				Bnum = atoi(optarg);
				break;
			case 'C':
				c += 2;
				fA = fB = fC = 1;
				Cnum = atoi(optarg);
				Anum = Cnum;
				Bnum = Cnum;
				break;
			case 'b':
				c++;
				fb = 1;
				break;
			case 'c':
				c++;
				fc = 1;
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
				c += 2;
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
				fprintf(stderr, "Usage: grep [OPTION & argument if any]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
				exit(0);
		}
	}
	
	
	if(fq) { //-q
		exit(0);
	}
	if(argc == 1) {
		printf("Usage: ./grep [OPTION]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
		exit(0);
	}
	if(argc == 2 && (strcmp(argv[1], "-r")) == 0) {
		printf("Usage: ./grep [OPTION]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
		exit(0);
	}
	if(ff) {
		if(argc < 4) {
			if(fs) //-s
				exit(0);
			errno = EINVAL;
			printf("Usage: ./grep [OPTION]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
			return errno;
		}
		nof = argc - (c + 2);
		fd = open(fnam, O_RDONLY);
		if(fd == -1) {
			if(fs) //-s
				exit(0);
			printf("./grep: %s: No such file or directory\n", fnam);
			exit(errno);
		}
		while(x) {
			a = 0;
			while(ch != '\n' && x) {
				x = read(fd, &ch, sizeof(char));
				pattern[a] = ch;
				a++;
			}
			ch = '\0';
			pattern[a - 1] = '\0';
			//printf("%s\n", pattern);
			for(i = c + 2; i < argc; i++) {
				if(fv) {
					grepv(argv[i], pattern);
				}
				else if(fx) {
					grepx(argv[i], pattern);
				}
				else {
					//printf("LALALA %s LALALA", pattern);
					grep(argv[i], pattern);
				}
			}
		}
		exit(0);
	}
		

			
	strcpy(pattern, argv[c + 1]);
	if(fi || fy) { //-i -y
		strlwr(pattern);
	}
	nof = argc - (c + 2);
	if(fr || fR) { //-r -R
		if(nof == 0) {
			fH = 1;
			listdir(".", 0);
			exit(0);
		}
	}
	if(!nof) {
		printf("Usage: ./grep [OPTION]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
	}
	if (argc < 3) {
		if(fs) //-s
			exit(0);
		errno = EINVAL;
		printf("Usage: ./grep [OPTION]... PATTERN [FILE]...\nTry './grep --help' for more information.\n");
		return errno;
	}
	for(i = c + 2; i < argc; i++) {
		if(fv) {
			grepv(argv[i], pattern);
		}
		else if(fx) {
			grepx(argv[i], pattern);
		}
		else if(fw) {
			grepw(argv[i], pattern);
		}
		else {
			grep(argv[i], pattern);
		}
	}
	return 0;
}
