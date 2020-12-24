//#define _CRT_SECURE_NO_WARNINGS//просто так надо
#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
//#include <algorithm>
#define SIZE 80
#define SIZE_S2 20

void q_sort(int* arr, int size) {
	//Указатели в начало и в конец массива
	int i = 0;
	int j = size - 1;

	//Центральный элемент массива
	int mid = arr[size / 2];

	//Делим массив
	do {
		//Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
		//В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
		while (arr[i] < mid) {
			i++;
		}
		//В правой части пропускаем элементы, которые больше центрального
		while (arr[j] > mid) {
			j--;
		}

		//Меняем элементы местами
		if (i <= j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);


	//Рекурсивные вызовы, если осталось, что сортировать
	if (j > 0) {
		//"Левый кусок"
		q_sort(arr, j + 1);
	}
	if (i < size) {
		//"Првый кусок"
		q_sort(&arr[i], size - i);
	}
}

int main()
{
	//setlocale(LC_ALL, "rus"); не сработает, тк не даст вводить кириллицу в массив. А мы хотим
	SetConsoleCP(1251);//утанавливаем кириллицу в консоль на ввод
	SetConsoleOutputCP(1251);//утанавливаем кириллицу в консоль на вывод


	int copycounter = 0;//счетчик вхождения строки S2 в S1
	int wordcounter = 0;//счетсик слов

	char S1[SIZE];
	char S2[SIZE_S2];

	//вводим строки
	std::cout << "Enter your string: ";
	std::cin.getline(S1, 80);//getline, потому что хотим вводить до enter-a, а не до любого разделителя
	std::cout << "Enter your second string: ";
	std::cin.getline(S2, 20);
	//////////


	std::cout << std::endl;

	//////////////////////1
	int strlnS2 = strlen(S2) - 1;
	int strlnS1 = strlen(S1) - 1;
	int* pCounter = new int[2 * (SIZE - 1)];//массив координат вхождения ключа
	int count_pCount = 0;//статус заполненности pCounter
	char* pS1 = S1;//указатель на массив для дальнейшего поиска
	for (;;)
	{
		pS1 = strstr(pS1, S2);//ищем первое вхождение S2 в S1
		if (pS1 == NULL)//если S1 не содержит S2
		{
			break;
		}
		else
		{
			pCounter[count_pCount] = strlnS1 - (strlen(pS1) - 1);
			count_pCount++;
			pCounter[count_pCount] = strlnS1 - (strlen(pS1) - 1) + strlnS2 + 1;
			count_pCount++;
			pS1++;//перемещаем указатель в следующую ячейку, после ячейки найденного вхождения
			copycounter++;//+1 совпадающая со строкой подстрока
		}
	}
	std::cout << "S2 is contained in S1 N times: N = " << copycounter << std::endl;
	//////////////////////1



	//////////////////////3
	char max = '0';//выведем это, если букв нет
	int max_count = 0;
	int max_old_count = 0;
	pS1 = S1;
	int ASCII;
	for (int i = 0; i < SIZE; i++, max_count = 0)
	{

		ASCII = (int)S1[i];
		if (!((ASCII >= 65 && ASCII <= 90) || (ASCII >= 97 && ASCII <= 122) || (ASCII < 0)))//это буква? 
			continue;

		pS1 = S1;
		for (;*pS1!='\0';)//поиск копий
		{
			pS1 = strchr(pS1, S1[i]);
			if (pS1 == NULL)
			{
				break;
			}
			else
			{
				pS1++;
				max_count++;
			}
		}
		if (max_count > max_old_count)//если копий новой буквы больше, чем копий старой
		{
			max = S1[i];
			max_old_count = max_count;
		}
	}
	std::cout << "The most frequent letter is " << max << std::endl;
	//////////////////////3



	//////////////////////2

	///Да, по сути copycounter и count_pCount выполняют одну и ту же функциЮ а значит одно можно заменить другим. Но т.к они нужны для разных заданий, я решил оставить обе переменные
	count_pCount--;//уточням заполенность массива pCount
	int lght = strlen(S1);//оптимизация
	char* S3 = new char[lght + 2 * copycounter + 1];//содаем новый массив для ответа на задание N2, +1 элемеент под \0
	
	/*int temp = 0;//переменная для сортировки пузырьком

	for (int i = 0; i < count_pCount - 1; i++) {
		for (int j = 0; j < count_pCount - i - 1; j++) {
			if (pCounter[j] > pCounter[j + 1]) {
				// меняем элементы местами
				temp = pCounter[j];
				pCounter[j] = pCounter[j + 1];
				pCounter[j + 1] = temp;
			}
		}
	}
	*///////на случай, если qsort не сработает

	q_sort(pCounter, count_pCount);
	int increment = 0;
	int k = 0;//оптимизация по времени выполнения
	int u = 0;//c-к переноса S1 в S3
	for (int i = 0; i < lght + 2 * copycounter + 1; i++)
	{
		if (i == pCounter[k] + increment)
		{
			S3[i] = '"';
			k++;
			increment++;
			/*for (int j = k; j < 2 * copycounter; j++)
			{
				pCounter[j]++;
			}*/
		}
		else
		{
			S3[i] = S1[u];
			u++;
		}
	}
	std::cout << "New array S3: " << S3 << std::endl;
	delete[] S3;
	delete[] pCounter;
	//////////////////////2


	//////////////////////4
	std::cout << "exercise 4:" << std::endl;
	char* next_token = 0;
	char* idk = strtok_s(S1, " .,!?:;", &next_token);//idk - потому что я понятия не имею как это рботает UPD: на доп занятии объяснили
	while (idk != NULL)
	{
		std::cout << idk << std::endl;
		wordcounter++;
		idk = strtok_s(NULL, " .,!?:;", &next_token);
	}
	//////////////////////4



	system("pause");
	return 47;
}