#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>  
#include <stdlib.h>
FILE* cub;
int createcub()
{
	char c[10], m[10],y;  
	int s;  
	cub = fopen("cubes.dat", "w");  
	if (cub == NULL) return 1;      
	printf("Input:\n");
	while(true){
		if (scanf("%d %s %s", &s, c, m) == 3) {
			if (s > 0 && (strcmp(c, "red") == 0 || strcmp(c, "orange") == 0 || strcmp(c, "yellow") == 0 || strcmp(c, "green") == 0 || strcmp(c, "blue") == 0 || strcmp(c, "indigo") == 0 || strcmp(c, "violet") == 0) && (strcmp(m, "metal") == 0 || strcmp(m, "tree") == 0 || strcmp(m, "carton") == 0)) {
				if (getchar() != '\n') {
					puts("incorrect input");
					while (getchar() != '\n');
				}
				else {
					fprintf(cub, "%2d%-9.9s%-9.9s", s, c, m);
				}
			}
			else {
				puts("incorrect input");
				while (getchar() != '\n');
			}
		}
		else {
			while (getchar() != '\n');
			puts("Stop input? y/n");
			scanf("%c", &y);
			if (getchar() != '\n' && (y!='y'||y!='n')) {
				puts("incorrect input");
				while (getchar() != '\n');
			}
			else {
				if (y == 'y') break;
			}
		}
	};
	fclose(cub);
	return 0;
}
int output() {
	char color[10], material[10];
	int num;
	cub = fopen("cubes.dat", "r"); 
	if (cub == NULL) return 1;
	puts("Your file:");
	while ((fscanf(cub, "%2d%9s%9s", &num, color, material)) != EOF) {
		printf("%d %s %s\n", num, color, material);
	}
	fclose(cub);   
	return 0;
}
int search()
{
	int red = 0, orange = 0, yellow = 0, green = 0, blue = 0, indigo = 0, violet = 0, v = 0, s;
	long l; char c[10];
	cub = fopen("cubes.dat", "r");  if (cub == NULL) return 1;
	for (int i = 0; fscanf(cub, "%2d%9s", &s, c) != EOF; i++) {
				if (strcmp(c, "red")==0) {
					red += 1;
					v += s * s;
				}
				else if (strcmp(c, "orange")==0) {
					orange += 1;
					v += s * s;
				}
				else if (strcmp(c, "yellow")==0) {
					yellow += 1;
					v += s * s;
				}
				else if (strcmp(c, "green")==0) {
					green += 1;
					v += s * s;
				}
				else if (strcmp(c, "blue")==0) {
					blue += 1;
					v += s * s;
				}
				else if (strcmp(c, "indigo")==0) {
					indigo += 1;
					v += s * s;
				}
				else if (strcmp(c, "violet")==0) {
					violet += 1;
					v += s * s;
				}
				l = (i + 1) * 20;
				if (fseek(cub, l, 0) != 0) return 2;
	}
	printf("red: %d\nornage: %d\nyellow: %d\ngreen: %d\nblue: %d\nindigo: %d\nviolet: %d\ntotal volume: %d\n", red, orange, yellow, green, blue, indigo, violet, v);
	return 0;
}
int main()
{
	switch (createcub())
	{
	case 1: printf("Error: file is not created!Abort "); exit(1); 
	case  0: printf("file is created!\n\n"); break;
	}
	switch (output())
	{
	case 1: printf("cannot open file for reading!Abort\n"); exit(1);
	case  0: printf("Successful reading!\n\n"); break;
	}
	switch (search())
	{
	case 1: printf("cannot open file for reading!Abort"); exit(1);
	case 2: printf("Bad with funution \"fseek\"Abort "); exit(1);
	case  0: printf("Successfully completed!\n\n"); break;
	}
	return 0;
}





