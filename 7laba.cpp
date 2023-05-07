#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <ctime>
#include <string.h>
int check_int(int from, int to);//проверка ввода целых чисел(нужно для меню)
int ru_en_menu(char n[]);
int en_ru_menu(char n[]);
int ru_en(char n[], char file_name[], char file_name2[], int k);
int reset(char n[], char file_name[], char fil_name2[]);//очищение прогресса
int file_copy(char n1[], char n2[]);//копирование одного файла в другой полностью
int append_file(char n[], char line[]);//добавление строки в файл
int delete_str(char n[], char line[]);//удаление строки из файла
int get_words(char *& en, char *& ru, char line[], char file_name[], char line2[]);//получение строки и двух распарсенных слов англ и рус из файла
int repeat(char file_name2[]);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char n[12] = "english.txt";
	while (true) {
		system("cls");
		puts("                    Лексика английского языка");
		puts("1. Дано английское слово,нужно указать перевод на русский\n2. Дано русское слово, нужно указать перевод на английский\n3. Выход\n");
		printf("Выберите пункт:   ");
		switch (check_int(0, 4)) {
		case 1: en_ru_menu(n); break;
			//case 1: an_ru(); break;
		case 2: ru_en_menu(n); break;
			//case 3: input(); break;
		case 3:return 0;
		}
	}
}

//проверка ввода номера пункта
int check_int(int from, int to) {
	int res, f;
	char ch, ch1;
	do {
		while ((scanf("%d", &res) != 1))
		{ //Ошибка ввода. Надо очистить входной поток от "не числа" 
			while (getchar() != '\n');
			printf("ошибка\n");
		}
		f = 0;
		if (res <= from || res > to) {
			printf("ошибка\n");
		}
		ch = getchar();
		if (ch != '\n' && ch != ' ') {
			puts("ошибка");
			f = 1;
			while (getchar() != '\n');
		}
		else if (ch == ' ') {
			do {
				ch1 = getchar();
				if (ch1 != ' ' && ch1 != '\n') {
					f = 1;
					puts("ошибка.");
					break;
				}
			} while (ch1 != '\n');
		}
	} while (((res <= from || res > to || f == 1)));
	return res;
}

//меню английский-русский
int en_ru_menu(char n[]) {
	char file_name[30] = "english_en_ru_to_study.txt", file_name2[30] = "english_en_ru_finish.txt";
	while (true) {
		system("cls");
		puts("1. Приступить к изучению\n2. Сбросить прогресс\n3. Повторение изученного\n4. Вернуться в главное меню\n");
		printf("Выберите пункт:   ");

		switch (check_int(0, 4)) {
		case 1: ru_en(n, file_name, file_name2, 1); break;
		case 2: reset(n, file_name, file_name2); break;
		case 3:repeat(file_name2); break;
		case 4: return 0;
		}
	}
}

//меню русский-английский
int ru_en_menu(char n[]) {
	char file_name[30] = "english_ru_en_to_study.txt", file_name2[30] = "english_ru_en_finish.txt";
	while (true) {
		system("cls");
		puts("1. Приступить к изучению\n2. Сбросить прогресс\n3. Повторение изученного\n4. Вернуться в главное меню\n");
		printf("Выберите пункт:   ");

		switch (check_int(0, 4)) {
		case 1: ru_en(n, file_name, file_name2, 2); break;
		case 2: reset(n, file_name, file_name2); break;
		case 3:repeat(file_name2); break;
		case 4: return 0; 
		}
	}
}

//повтроени
int repeat(char file_name2[]) {

	char line[100] = { 0 }, line2[100], * en = 0, * ru = 0, answer[50], help;
	while (true) {
		system("cls");
		if (get_words(en, ru, line, file_name2, line2) == 1) {
			puts("Пока ещё нет слов для повторения\nНажмите любую клавишу для продолжения...");//получение рандомных слов
			getchar();
			return 1;
		}
		printf("            %s\n\n", ru);
		printf("Введите ответ или '###' для выхода:   ");
		scanf("%s", answer);
		while (getchar() != '\n');
		if (strcmp(answer, "###") == 0) return 0;
		else if (strcmp(answer, en) == 0) {
			puts("Верно!\n");
		}
		else printf("Вы ошиблись!Правильный ответ: %s\n", en);
		printf("\nНажмите любую клавишу для продолжения...");
		getchar();
	}

}
//очищение погресса
int reset(char n[], char file_name[], char file_name2[]) {
	FILE* fp;
	system("cls");
	//копируем из основного файла 
	file_copy(file_name, n);//2-src

	if (!(fp = fopen(file_name2, "w"))) puts("ошибка!");
	else (puts("Прогресс очищен!\nНажмите любую кдавишу для продолжения..."));
	fclose(fp); getchar(); return 0;
}

int ru_en(char n[], char file_name[], char file_name2[], int k) {
	char line[100] = { 0 }, line2[100], * en = 0, * ru = 0, answer[50];
	while (true) {
		system("cls");
		//копируем из основного файла 
		//file_copy(file_name, n);//2-src
		//while(true){}
		if(get_words(en, ru, line, file_name, line2)==1) {
			puts("Пока ещё нет слов для повторения\nНажмите любую клавишу для продолжения...");//получение рандомных слов
			getchar();
			return 1;
		}//получение рандомных слов
		//printf("liiiineee   %s\n", line2);
		if (k == 2) {
			printf("            %s\n\n", ru);
		}
		else {
			printf("            %s\n\n", en);
		}
		printf("Введите ответ или '###' для выхода:   ");
		//fgets(answer,sizeof(answer), stdin);
		scanf("%s", answer);
		while (getchar() != '\n');
		if (k == 2) {
			if (strcmp(answer, "###") == 0) return 0;
			else if (strcmp(answer, en) == 0) {
				append_file(file_name2, line2);//ответ верный и удалить надо будет
				delete_str(file_name, line2);
				puts("Верно!\n");
			}
			else printf("Вы ошиблись!Правильный ответ: %s\n", en);
		}
		else {

			if (strcmp(answer, "###") == 0) return 0;
			else if (strcmp(answer, ru) == 0) {
				append_file(file_name2, line2);//ответ верный и удалить надо будет
				delete_str(file_name, line2);
				puts("Верно!\n");
			}
			else printf("Вы ошиблись!Правильный ответ: %s\n", ru);

		}
		printf("\nНажмите любую клавишу для продолжения...");
		getchar();
	}
	//delete en; delete ru;
}

//удаление строки из файла 
int delete_str(char n[], char line[]) {
	FILE* fp, * fp2; char buf[100];
	if (!(fp = fopen(n, "r"))) { puts("ошибка при открытии файла для чтения"); return 1; }

	if ((fp2 = fopen("-.txt", "r"))) {
		puts("На вашем устройстве уже имеется файл с именем \"-.txt\"(промежуточный файл в программе).Возможна потеря данных.Для отмены действий введите #\n");
		fclose(fp2);
		if (getchar() == '#') return 2;
	}
	if (!(fp2 = fopen("-.txt", "w"))) { puts("ошибка при открытии промежуточного файла для записи"); return 3; }

	while (fscanf(fp, "%s", buf) != EOF && strcmp(buf, "\n") != 0) {                            // пока не конец файла
		if (strcmp(buf, line) != 0) {
			fprintf(fp2, "%s\n", buf);
		}
	}
	fclose(fp); fclose(fp2);
	remove(n);
	rename("-.txt", n);
}
//добавление строки в файл для уже выученных слов
int append_file(char n[], char line[]) {
	FILE* fp;
	if ((fp = fopen(n, "r")) == 0) {
		if (!(fp = fopen(n, "w"))) puts("Ошибка при открытии файла для записи!");
	}
	else {
		if (!(fp = fopen(n, "a"))) { printf("Ошибка при добавлении в файл %s данных\n", n); return 1; }
	}
	fprintf(fp, "%s\n", line);
	fclose(fp);
}

//копирование одного файла в другой полностью
int file_copy(char n1[], char n2[]) {//2-src
	FILE* fp1, * fp2; char buf[100];
	if (!(fp1 = fopen(n1, "w"))) { printf("Файл %s не открылся для записи\n"); return 1; }
	if(!(fp2=fopen(n2, "r"))) { printf("Файл %s не открылся для чтения\n", n2); return 1; }
	while (!feof(fp2))                             // пока не конец файла
	{
		fscanf(fp2, "%s", buf);                                    // прочитать символ из файла
		fprintf(fp1, "%s\n", buf);
	}
	fclose(fp1); fclose(fp2);
	return 0;
}

//получение строки и двух распарсенных слов англ и рус из файла
int get_words(char *& en, char *& ru, char line[], char file_name[], char line2[]) {
	FILE* fp; char buffer[100], buffer2[100]; unsigned i = 0; int c, cstr=0;
	if (!(fp = fopen(file_name, "r"))) printf("Файл \"%s\" не найден!\n", file_name);
	srand(time(0));
	//подсчёт строк в файле
	while (fscanf(fp, "%s", buffer)!=EOF&&strcmp(buffer, "\n") != 0) {
		cstr += 1;
	}
	if (cstr == 0) return 1;
	fseek(fp, 0L, 0);
	//рандоманая строка из файла
	c = 1+rand() % cstr;
	//printf("cccccccccccccccc %d\n",c );
	for (int i = 1; i <= cstr; i++) {
		fscanf(fp, "%s", buffer);
		if (i == c) {
			strcpy(line, buffer); break;
		}
	 }
	//while (fgets(buffer, sizeof buffer, fp) != NULL)
	//	if (rand() % ++i == 0)
	//		strcpy(line, buffer);
	strcpy(line2, buffer);
	//printf("ininin %s", buffer);
	en = strtok(line, "-\n");
	ru = strtok(NULL, "-\n");
	//printf("В гет вордс %s   %s\n", en, ru);
	fclose(fp);
	//line[strlen(line) - 1] = '\0';
}