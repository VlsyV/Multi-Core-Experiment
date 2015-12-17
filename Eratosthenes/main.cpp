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
		cout << "区间[" << min<< "," << max << "]" << "共有"<<primeNum<<"个素数"<<endl;
	}
		
}

void Eratos3(int prime[], int length, int B,int min, int max, int &primeNum)
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

	cout << "区间[" << pn + 1 << "," << right << "]" << endl;
	cout << "素数个数:" << Num << endl;
	cout << "素数区间:" << "[" << result[length] << "," << result[Num + length - 1] << "]" << endl;

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

	for (int i = 0; i < Num+length; i++)
	{
		if (result[i] >= min&&result[i] <= max)
			primeNum++;
	}

	if (right < max)
	{
		Eratos3(result, Num + length, B, min, max, primeNum);

	}
	else
	{
		cout << "区间[" << min << "," << max << "]" << "共有" << primeNum << "个素数" << endl;
	}

}


int main()
{
	int  initPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	clock_t start, end;

	int max = Power(2, 26);

	start = clock();
	
	int primeNum = 0;

	//int * isPrime = new int[max];
	//Eratos(isPrime, max);

	//for (int i = 9409; i < max; i++)
	//{
	//	if (isPrime[i] == 1)
	//		primeNum++;
	//}
	//cout << "区间[" << 9409 << "," << max << "]" << "素数个数：" << primeNum << endl;

	
	Eratos2(initPrime, 25, Power(2, 10), Power(2, 12),primeNum);

	primeNum = 0;
	int B = 4 * Power(2, 10);
	Eratos3(initPrime, 25,B, Power(2, 10), Power(2, 12), primeNum);

	end = clock();
	cout << "共花费" << (end - start)  << "（us）" << endl;


	
}

