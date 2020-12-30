//#include<bits/stdc++.h> 
#include<stdlib.h>
#include <iostream>
#include<time.h>
#include <omp.h>

#ifndef MATRIX_HEADER
#define MATRIX_HEADER
#define NUM_THREADS 8

using namespace std;

void Initalize_Values(double **matrix_M, int n)
{
	//srand(time(0) + rand() % 599);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix_M[i][j] = 1; //rand()%10;	
	//srand(time(0) + rand() % 299);
	/*srand() fonksiyonu, seed_rand teriminin kýsaltýlmýþýdýr [6]. Hassas iþlerde, her seferinde farklý rasgele sayýlar elde edebilmenin bir yolu, her koþmada seed’in kullanýcýdan baðýmsýz olarak deðiþtirilmesi için programa eklenmiþtir. */
}

void Initalize_Values(float **matrix_fM, int n)
{
	//srand(time(0) + rand() % 39);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix_fM[i][j] = 1; //rand()%10;	
	//srand(time(0) + rand() % 49);
}

void Display(double **matrix_M, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%lf ", matrix_M[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void Display(float **matrix_fM, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f ", matrix_fM[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix_Multiply_Serial(double **matrix_M1, double **matrix_M2, double **matrix_Result, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			matrix_Result[i][j] = 0;
			for (k = 0; k < n; k++)
				matrix_Result[i][j] += matrix_M1[i][k] *
				matrix_M2[k][j];
		}
}

void Matrix_Multiply_Serial(float **matrix_fM1, float **matrix_fM2, float **matrix_fResult, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			matrix_fResult[i][j] = 0;
			for (k = 0; k < n; k++)
				matrix_fResult[i][j] += matrix_fM1[i][k] *
				matrix_fM2[k][j];
		}
}

void Matrix_Multiply_Parallel(double **matrix_M1, double **matrix_M2, double **matrix_Result, int n)
{
	omp_set_num_threads(NUM_THREADS);		

	int i, j, k;
#pragma omp parallel for private(i,j,k) shared(matrix_M1,matrix_M2,matrix_Result)
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			matrix_Result[i][j] = 0;
			for (k = 0; k < n; k++)
				matrix_Result[i][j] += matrix_M1[i][k] * matrix_M2[k][j];
		}
}

void Matrix_Multiply_Parallel(float **matrix_fM1, float **matrix_fM2, float **matrix_fResult, int n)
{
	omp_set_num_threads(NUM_THREADS);		

	int i, j, k;
#pragma omp parallel for private(i,j,k) shared(matrix_fM1,matrix_fM2,matrix_fResult)
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			matrix_fResult[i][j] = 0;
			for (k = 0; k < n; k++)
				matrix_fResult[i][j] += matrix_fM1[i][k] * matrix_fM2[k][j];
		}
}



#endif