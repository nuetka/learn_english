#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <conio.h> 
#define N 30
int create(char *fname1)
{
	FILE* fp1;
	int digit, n, flag=0, count=0;
	fp1 = fopen(fname1, "w");
	if (fp1 == NULL)
	{
		printf("Error: don't open %s for writing \n", fname1);
		return 2;
	}
	do {
		flag = 0;
		puts("Enter number of digit and this number should be divided by 12");
		if ((scanf("%d", &n)) == 1)
		{
			if (n % 12 != 0)
			{
				puts("Incorrect input");
				flag = 1;
			}
		}
		else {
			flag = 1; 
			puts("Incorrect input");
		}
	} while (flag == 1);
	fprintf(fp1, "%d ", n);
	printf("Enter %d digits, digits not equal to zero\n", n);
	for (int i = 0; i < n; i++)
	{
		do {
			flag = 0;
			if ((scanf("%d", &digit)) == 1)
			{
				if (digit == 0)
				{
					puts("Incorrect input");
					flag = 1;
				}
				//для записи ++ -- ++ --
				else if (count%2==0 && digit<0){// чёт - положит
				
					puts("Incorrect input");
					flag = 1;
				}
				else if (count % 2 == 1 && digit>0) {// нечёт - отриц
					puts("Incorrect input");
					flag = 1;
				}
			}
			else {
				flag = 1; puts("Incorrect input");
			}
		} while (flag == 1);
		if (i % 2 != 0) {
			count += 1;
		}
		fprintf(fp1, "%d ", digit);
	}
	fclose(fp1);
	printf("%s is created!", fname1);
	return 0;
}
int output(char* fname)
{
	FILE* fp;
	int digit, n;
	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		printf("Error: don't open %s for reading\n", fname );
		return 1;
	}
	fscanf(fp, "%d", &n);
	printf("Your file:\n");
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%d", &digit);
		printf("%d ", digit);
	}
	fclose(fp);
	return 0;
}
int new_create(char *fname1, char *fname2)
{
	FILE* fp;
	FILE* fnew;
	int digit, n, len, count, count1;
	fnew = fopen(fname2, "w");
	if (fnew == NULL)
	{
		puts("error");
		return 1;
	}
	fp = fopen(fname1, "r");
	if (fp == NULL)
	{
		puts("error");
		return 1;
	}
	len = fscanf(fp, "%d", &n);
    count1 = n / 12;
	
	while (count1 != 0)
	{	
		int help[12];
		for (int i = 0; i < 12; i++)
			fscanf(fp, "%d", &help[i]);
		int* positiv = &help[0];
		int* negativ = &help[2];
		for (int i = 0; i < 2; i++)
		{
			count = 0;
			while (count < 3)
			{
				if (*positiv > 0)
				{
					fprintf(fnew, "%d ", *positiv);
					count++;
				}
				positiv++;
			}
			count = 0;
			while (count < 3)
			{
				if (*negativ < 0)
				{
					fprintf(fnew, "%d ", *negativ);
					count++;
				}
				negativ++;
			}
		}
		count1--;
	}
	fclose(fnew);
	fclose(fp);
	return n;
}
int output_new(int len, char* fname)
{
	FILE* fnew;
	int new_digit;
	fnew = fopen(fname, "r");
	if (fnew == NULL)
	{
		puts("error");
		return 1;
	}
	printf("Your new file:\n");
	for (int i = 0; i < len; i++)
	{
		fscanf(fnew, "%d", &new_digit);
		printf("%d ", new_digit);
	}
	fclose(fnew);
}
int main(int argc, char* arg[]) {
	FILE* fp1;
	FILE* fp2;
	int check, len;
	fp1 = fopen(arg[1], "r");
	if (fp1 != NULL)
	{
		printf("Error: %s already exists. Still continue - 1\n", arg[1]);
     	fclose(fp1);
		scanf("%d", &check);
		if (check != 1) {
			return 1;
		}
	}
	fp2 = fopen(arg[2], "r");
	if (fp2 != NULL)
	{
		printf("Error: %s already exists. Still continue - 1 \n", arg[2]);
		fclose(fp2);
		scanf("%d", &check);
		if (check != 1) {
			return 1;
		}
	}

	create(arg[1]);
	printf("contents of %s:\n", arg[1]);
	output(arg[1]);
	len=new_create(arg[1],arg[2]);
	printf("contents of %s:\n", arg[2]);
	output_new(len, arg[2]);
	return 0;
}