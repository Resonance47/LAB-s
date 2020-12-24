//#define _CRT_SECURE_NO_WARNINGS//������ ��� ����
#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
//#include <algorithm>
#define SIZE 80
#define SIZE_S2 20

void q_sort(int* arr, int size) {
	//��������� � ������ � � ����� �������
	int i = 0;
	int j = size - 1;

	//����������� ������� �������
	int mid = arr[size / 2];

	//����� ������
	do {
		//��������� ��������, ���� ��, ������� ����� ���������� � ������ �����
		//� ����� ����� ������� ����������(��������� �� �����) ��������, ������� ������ ������������
		while (arr[i] < mid) {
			i++;
		}
		//� ������ ����� ���������� ��������, ������� ������ ������������
		while (arr[j] > mid) {
			j--;
		}

		//������ �������� �������
		if (i <= j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);


	//����������� ������, ���� ��������, ��� �����������
	if (j > 0) {
		//"����� �����"
		q_sort(arr, j + 1);
	}
	if (i < size) {
		//"����� �����"
		q_sort(&arr[i], size - i);
	}
}

int main()
{
	//setlocale(LC_ALL, "rus"); �� ���������, �� �� ���� ������� ��������� � ������. � �� �����
	SetConsoleCP(1251);//������������ ��������� � ������� �� ����
	SetConsoleOutputCP(1251);//������������ ��������� � ������� �� �����


	int copycounter = 0;//������� ��������� ������ S2 � S1
	int wordcounter = 0;//������� ����

	char S1[SIZE];
	char S2[SIZE_S2];

	//������ ������
	std::cout << "Enter your string: ";
	std::cin.getline(S1, 80);//getline, ������ ��� ����� ������� �� enter-a, � �� �� ������ �����������
	std::cout << "Enter your second string: ";
	std::cin.getline(S2, 20);
	//////////


	std::cout << std::endl;

	//////////////////////1
	int strlnS2 = strlen(S2) - 1;
	int strlnS1 = strlen(S1) - 1;
	int* pCounter = new int[2 * (SIZE - 1)];//������ ��������� ��������� �����
	int count_pCount = 0;//������ ������������� pCounter
	char* pS1 = S1;//��������� �� ������ ��� ����������� ������
	for (;;)
	{
		pS1 = strstr(pS1, S2);//���� ������ ��������� S2 � S1
		if (pS1 == NULL)//���� S1 �� �������� S2
		{
			break;
		}
		else
		{
			pCounter[count_pCount] = strlnS1 - (strlen(pS1) - 1);
			count_pCount++;
			pCounter[count_pCount] = strlnS1 - (strlen(pS1) - 1) + strlnS2 + 1;
			count_pCount++;
			pS1++;//���������� ��������� � ��������� ������, ����� ������ ���������� ���������
			copycounter++;//+1 ����������� �� ������� ���������
		}
	}
	std::cout << "S2 is contained in S1 N times: N = " << copycounter << std::endl;
	//////////////////////1



	//////////////////////3
	char max = '0';//������� ���, ���� ���� ���
	int max_count = 0;
	int max_old_count = 0;
	pS1 = S1;
	int ASCII;
	for (int i = 0; i < SIZE; i++, max_count = 0)
	{

		ASCII = (int)S1[i];
		if (!((ASCII >= 65 && ASCII <= 90) || (ASCII >= 97 && ASCII <= 122) || (ASCII < 0)))//��� �����? 
			continue;

		pS1 = S1;
		for (;*pS1!='\0';)//����� �����
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
		if (max_count > max_old_count)//���� ����� ����� ����� ������, ��� ����� ������
		{
			max = S1[i];
			max_old_count = max_count;
		}
	}
	std::cout << "The most frequent letter is " << max << std::endl;
	//////////////////////3



	//////////////////////2

	///��, �� ���� copycounter � count_pCount ��������� ���� � �� �� ������� � ������ ���� ����� �������� ������. �� �.� ��� ����� ��� ������ �������, � ����� �������� ��� ����������
	count_pCount--;//������� ������������ ������� pCount
	int lght = strlen(S1);//�����������
	char* S3 = new char[lght + 2 * copycounter + 1];//������ ����� ������ ��� ������ �� ������� N2, +1 �������� ��� \0
	
	/*int temp = 0;//���������� ��� ���������� ���������

	for (int i = 0; i < count_pCount - 1; i++) {
		for (int j = 0; j < count_pCount - i - 1; j++) {
			if (pCounter[j] > pCounter[j + 1]) {
				// ������ �������� �������
				temp = pCounter[j];
				pCounter[j] = pCounter[j + 1];
				pCounter[j + 1] = temp;
			}
		}
	}
	*///////�� ������, ���� qsort �� ���������

	q_sort(pCounter, count_pCount);
	int increment = 0;
	int k = 0;//����������� �� ������� ����������
	int u = 0;//c-� �������� S1 � S3
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
	char* idk = strtok_s(S1, " .,!?:;", &next_token);//idk - ������ ��� � ������� �� ���� ��� ��� ������� UPD: �� ��� ������� ���������
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