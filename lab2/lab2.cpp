#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#pragma warning(disable:4996)


/*примеры:
SEND+MORE=MONEY
ELEVEN+NINE+FIVE+FIVE=THIRTY
*/
#define max 10 //максимум 10 различных букв может быть

char letters[max]; //хранит используемые буквы
int lettInt[max];// хранит присвоенные значения буквам
bool used[max];
int lettersSize = 0; //кол-во используемых букв
char** words=(char**)malloc(sizeof(char*));//здесь храним все слова(последнее - это результат)
int lettNoZero[max];
int wordCount = 0;//кол-во слов
float start;

//переводит буквенный массив соответсвтенно в число
unsigned long int toNumber(char arr[])
{
	unsigned long int number = 0;
	int sizeArr = strlen(arr);
	for (int i = 0; i < sizeArr; i++)
	{
		int j = 0;
		while (arr[i] != letters[j])
			j++;

		number = number+lettInt[j] * pow(10, sizeArr-i-1);
	}
	return number;
}

//запоминаем буквы в массив, size - кол-во уже помещенных букв, lett - буква
int alph(char lett)
{
	for (int i = 0; i <= lettersSize; i++)
	{
		if (lett == letters[i])
			return lettersSize;
	}
	if (lettersSize < max)
		letters[lettersSize] = lett;
	lettersSize++;

	return lettersSize;
}

//возвращает 1, если комбинация работает
int checkCombination()
{
	//проверка на 0
	int ind0 = -1; //индекс буквы, равной 0
	for (int i = 0; i < lettersSize; i++)
		if (lettInt[i] == 0)
			if (lettNoZero[i] == 1)
				return 0;


	int wordsInt[8];
	for (int i = 0; i < wordCount; i++)
		wordsInt[i] = toNumber(words[i]);

	int sum = 0;//сумма левой части выражения
	for (int i = 0; i < wordCount - 1; i++)
		sum += wordsInt[i];
	if (sum == wordsInt[wordCount - 1])
	{
		for (int i = 0; i < wordCount - 2; i++)
			printf("%d+", wordsInt[i]);
		printf("%d=", wordsInt[wordCount - 2]);
		printf("%d\n", wordsInt[wordCount - 1]);

		return 1;
	}
	else
		return 0;
}

void lex(int pos)
{
	if (pos == lettersSize) {

		if (checkCombination())
		{
			printf("Time - %f sec\n", (clock() - start) / CLOCKS_PER_SEC);
			exit(1);
		}
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (!used[i]) {						
			used[i] = true;					
			lettInt[pos] = i;				

			lex(pos + 1);

			lettInt[pos] = 0;
			used[i] = false;
		}
	}
}

int main()
{
	srand(time(NULL));

	char strAll[100]; //хранит введеное значение

	printf("enter rebus: ");
	scanf("%s", strAll);
	
	//засекаем время
	start = clock();
	/*запоминаем слова в массив строк, последняя строка - результат примера*/
	
	for (int i = 0; i < strlen(strAll); i++)
	{
		words = (char**)realloc(words, sizeof(char*) * (wordCount + 1));
		words[wordCount] = (char*)malloc(sizeof(char));
		int count = 0;//кол-во букв в слове
		while ((strAll[i] != '+')&&(strAll[i]!='=')&&(strAll[i]!='\0'))
		{
			words[wordCount][count] = strAll[i];
			count++;
			words[wordCount] = (char*)realloc(words[wordCount], sizeof(char) * (count+1));
			i++;
		}
		words[wordCount][count] = '\0';
		wordCount++;
	}

	int resultSize;//размер результата (для диапазона перебора)
	unsigned long long int lettersSizeMax; //максимальное значение результата
	resultSize = strlen(words[wordCount - 1]);
	//максимальное значение результата:
	

	/*запоминаем используемые буквы*/
	for (int i = 0; i < wordCount; i++)
	{
		int j = 0;
		while (words[i][j] != '\0')
		{
			lettersSize = alph(words[i][j]);
			j++;
		}
	}
	
	for (int i = 0; i < lettersSize; i++)
		for (int j = 0; j < wordCount; j++)
			if (letters[i] == words[j][0])
				lettNoZero[i] = 1;

	lex(0);

	return 0;
}
