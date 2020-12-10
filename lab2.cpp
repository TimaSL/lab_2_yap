#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

#define max 10 //максимум 10 различных букв может быть

char letters[max]; //хранит используемые буквы
int lettInt[max];// хранит присвоенные значения буквам
int lettersSize = 0; //кол-во используемых букв
char** words=(char**)malloc(sizeof(char*));//здесь храним все слова(последнее - это результат)
int wordCount = 0;//кол-во слов
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void print(int* a, int size) {
	int i = 0;
	while (i < size)
		printf("%2d ", a[i++]);
	printf("\n");
}

//чистка массива
void arrayClear(int a[], int size)
{
	for (int i = 0; i < size; i++)
		a[i] = -1;
}

//раскладывает число по цифрам
int toDigit(int A[], int a) {
	int i, n;
	for (i = 0, n = a; n != 0; i++, n = n / 10);
	int k = i--;                        // Количество цифр
	for (n = a; n != 0; i--, n = n / 10)
		A[i] = n % 10;        // Запись остатков в обратном порядке с конца
	return k;
}

//переводит буквенный массив соответсвтенно в число
int toNumber(char arr[])
{
	int number = 0;
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
int alph(char letters[],int size, char lett)
{
	for (int i = 0; i <= size; i++)
	{
		if (lett == letters[i])
			return size;
	}
	if (size < max)
		letters[size] = lett;
	size++;

	return size;
}

//возвращает 1, если комбинация работает
int checkCombination()
{
	//проверка на 0
	int ind0 = -1; //индекс буквы, равной 0
	for (int i = 0; i < lettersSize; i++)
		if (lettInt[i] == 0)
			ind0 = i;
	if (ind0 >= 0)
		for (int i = 0; i < wordCount; i++)
			if (words[i][0] == letters[ind0])
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
		printf("%d", wordsInt[wordCount - 1]);
		return 1;
	}
	else
		return 0;
}

//проверка на повторения в массиве, возвращает 1 если повторений нет
int repeatCheck(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = i+1; j < size; j++)
			if (arr[i] == arr[j])
				return 0;
	return 1;
}

int main()
{
	char strAll[100]; //хранит введеное значение

	printf("enter rebus: ");
	scanf("%s", strAll);
	
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
	int lettersSizeMax; //максимальное значение результата
	int lettersSizeMin; //минимальное значение результата
	resultSize = strlen(words[wordCount - 1]);
	//максимальное значение результата:
	lettersSizeMax = pow(10, resultSize) - 1;
	lettersSizeMin = pow(10, resultSize);

	/*запоминаем используемые буквы*/
	for (int i = 0; i < wordCount; i++)
	{
		int j = 0;
		while (words[i][j] != '\0')
		{
			lettersSize = alph(letters, lettersSize, words[i][j]);
			j++;
		}
	}
	
	int iI, jJ, r, k;
	long count = 0;         // число перестановок

	//при начальном заполнении учтем, что условие не выполнится при [0]=0
	lettInt[0] = 1;
	lettInt[1] = 0;
	for (iI = 2; iI < lettersSize; iI++)     // Начальное заполнение
		lettInt[iI] = iI;
	unsigned long int numberLong;
	numberLong = toNumber(letters);

	//начинаем перебор, функция сама распечатает результат, после чего произойдет выход из цикла.
	while (1)
	{
		toDigit(lettInt, numberLong);
		if (repeatCheck(lettInt, lettersSize))
			if(checkCombination())
				break;
		numberLong++;
		if( numberLong > 9999999999 ){
			numberLong = 0;
		}
	}
	return 0;
}