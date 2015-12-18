#include<iostream>
#include <time.h> 
#include<stdlib.h>

using namespace std;

int Power(int n,int p)
{
	int result = 1;
	for (int i = 0; i < p; i++)
		result *= n;
	return result;
}

//ԭʼ��������max���ڵ�����
void Eratos(int* isPrime,int max)
{
	for (int i = 2; i < max; i++)
		isPrime[i] = 1;
	for (int i = 2; i * i < max; i++)
	{
		if (isPrime[i])
			for (int j = i * i; j < max; j += i)
				isPrime[j] = 0;
	}
}

//���ó�ʼ���������Eratosɸ������ min��max���ڵ�������������������primeNum��
void Eratos2(int prime[], int length, int min, int max, int &primeNum)
{
	int pn = prime[length - 1];

	int right = max;
	if (pn*pn < max)
		right = pn*pn;

	int count = right - pn;
	char* A;
	A = new char[count];
	for (int i = 0; i < count; i++)
		A[i] = '0';

	int offset = pn + 1;
	for (int i = 0; i < length; i++)
	{
		int j = ceil((double)offset / prime[i]) * prime[i];
		while (j <= right)
		{
			if (j - offset>=0)
				A[j - offset] = '1';
			j += prime[i];
		}
	}

	int Num = 0;
	for (int i = 0; i < count; i++)
	{
		if (A[i] == '0')
			Num++;
	}

	int* result = new int[Num + length];
	for (int i = 0; i < length; i++)
		result[i] = prime[i];
	for (int i = 0, j = length; i < count; i++)
	{
		if (A[i] == '0')
			result[j++] = i + offset;
	}

	if (result[length]<min && result[Num + length - 1] > min)
	{
		for (int i = length; i < Num + length; i++)
			if (result[i] >= min)
				primeNum++;
	}
	else if (result[length] >= min && result[Num + length - 1] <= max)
	{
		primeNum += Num;
	}
	else if (result[length] < max&& result[Num + length - 1] >= max)
	{
		for (int i = length; i < Num + length; i++)
			if (result[i] <= max)
				primeNum++;
	}

	//for (int i = 0; i < Num+length; i++)
	//{
	//	if (result[i] >= min&&result[i] <= max)
	//		primeNum++;
	//}

	if (right < max)
	{
		Eratos2(result, Num+length, min, max, primeNum);

	}
	else
	{
		cout << "����[" << min<< "," << max << "]" << "����"<<primeNum<<"������"<<endl;
	}
		
}

//void Eratos3(int *prime, int length, int B, int *result, int &Num, int min, int max)
int* Eratos3(int *prime, int length, int B,  int &Num, int min, int max)
//void Eratos3(int prime[], int length, int B,int min, int max, int &primeNum)
{
	int pn = prime[length - 1];

	int right = pn+B;
	if (pn*pn < right)
		right = pn*pn;

	int count = right - pn;
	char* A;
	A = new char[count];
	for (int i = 0; i < count; i++)
		A[i] = '0';

	int offset = pn + 1;
	for (int i = 0; i < length; i++)
	{
		int j = ceil((double)offset / prime[i]) * prime[i];
		while (j <= right)
		{
			if (j - offset >= 0)
				A[j - offset] = '1';
			j += prime[i];
		}
	}

	Num = 0;
	for (int i = 0; i < count; i++)
	{
		if (A[i] == '0')
			Num++;
	}

	int*result = new int[Num];
	//result = (int*)malloc(Num*sizeof(int*));
	for (int i = 0, j = 0; i < count; i++)
	{
		if (A[i] == '0')
			result[j++] = i + offset;
	}

	return result;
	//cout << "����[" << pn + 1 << "," << right << "]" << endl;
	//cout << "��������:" << Num << endl;
	//cout << "��������:" << "[" << result[length] << "," << result[Num + length - 1] << "]" << endl;

	//if (result[length]<min && result[Num + length - 1] > min)
	//{
	//	for (int i = length; i < Num + length; i++)
	//		if (result[i] >= min)
	//			primeNum++;
	//}
	//else if (result[length] >= min && result[Num + length - 1] <= max)
	//{
	//	primeNum += Num;
	//}
	//else if (result[length] < max&& result[Num + length - 1] >= max)
	//{
	//	for (int i = length; i < Num + length; i++)
	//		if (result[i] <= max)
	//			primeNum++;
	//}

	//for (int i = 0; i < Num+length; i++)
	//{
	//	if (result[i] >= min&&result[i] <= max)
	//		primeNum++;
	//}

	//if (right < max)
	//{
	//	Eratos3(result, Num + length, B, min, max, primeNum);

	//}
	//else
	//{
	//	cout << "����[" << min << "," << max << "]" << "����" << primeNum << "������" << endl;
	//}

}


int main()
{
	int  initPrime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	int initLength = 25;

	int * initPrimeArr = new int[initLength];
	for (int i = 0; i < initLength; i++)
		initPrimeArr[i] = initPrime[i];
	
	clock_t start, end;

	start = clock();
	
	int primeNum = 0;

	//������׼
	//int max = Power(2, 26);
	//int * isPrime = new int[max];
	//Eratos(isPrime, max);

	//for (int i = 9409; i < max; i++)
	//{
	//	if (isPrime[i] == 1)
	//		primeNum++;
	//}
	//cout << "����[" << 9409 << "," << max << "]" << "����������" << primeNum << endl;

	//1.1
	//Eratos2(initPrimeArr, 25, Power(2, 25), Power(2, 26),primeNum);

	//1.2
	//primeNum = 0;
	int B = 4* Power(2, 10);
	//Eratos3(initPrimeArr, 25, B, Power(2, 25), Power(2, 26), primeNum);
	int min = Power(2, 25);
	int max = Power(2, 26);
	
	while (1)
	{
		int Num = 0;
		int *result = NULL;
		result = Eratos3(initPrimeArr, initLength, B, Num, min, max);

		cout << "��ʼ����[" << initPrimeArr[0] << "," << initPrimeArr[initLength - 1] << "]" << endl;
		cout << "��������:" << Num << endl;
		cout << "��������:" << "[" << result[0] << "," << result[Num - 1] << "]" << endl;
		cout << "����������:" << primeNum << endl;

		//����������������primeNum
		if (result[Num - 1 ]< min)
		{
			//����ɸѡ
			//�ϲ���ʼ����
			int *nextPrimeArr = new int[initLength + Num];

			for (int i = 0; i < initLength; i++)
			{
				nextPrimeArr[i] = initPrimeArr[i];
			}
			for (int i = 0; i < Num; i++)
			{
				nextPrimeArr[i + initLength] = result[i];
			}

			delete[] initPrimeArr;
			initPrimeArr = nextPrimeArr;
			nextPrimeArr = NULL;
		}
		else if (result[0] >= min&&result[Num - 1] <= max)
		{
			//����primeNum
			primeNum += Num;
			//����ɸѡ
			//�ϲ���ʼ����
			int *nextPrimeArr = new int[initLength + Num];

			for (int i = 0; i < initLength; i++)
			{
				nextPrimeArr[i] = initPrimeArr[i];
			}
			for (int i = 0; i < Num; i++)
			{
				nextPrimeArr[i + initLength] = result[i];
			}

			delete[] initPrimeArr;
			initPrimeArr = nextPrimeArr;
			nextPrimeArr = NULL;
		}
		else if (result[0] >= min && result[Num - 1] > max)
		{
			//����primeNum
			for (int i = 0; i < Num; i++)
			{
				if (result[i] <= max)
					primeNum++;
			}
			break;
		}
		else if (result[0] > max)
		{
			break;
		}

	}



	end = clock();
	cout << "������" << (end - start)  << "��us��" << endl;


	
}

