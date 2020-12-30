//#include <bits/stdc++.h>
#include<stdlib.h>
#include <iostream>
#include<time.h>
#include <omp.h>
#include "matrix_header.h"
using namespace std;

#define DIMENSION_N 1000
//#define debug_display


int main() {
	int n = DIMENSION_N;
	double **matrix_A, **matrix_B, **matrix_C;
	float **matrix_fA, **matrix_fB, **matrix_fC;
	double d_time, f_time, parallel_d_time, parallel_f_time;


	matrix_A = new double*[n];
	for (int i = 0; i < n; i++)
		matrix_A[i] = new double[n];

	matrix_B = new double*[n];
	for (int i = 0; i < n; i++)
		matrix_B[i] = new double[n];

	matrix_C = new double*[n];
	for (int i = 0; i < n; i++)
		matrix_C[i] = new double[n];

	matrix_fA = new float*[n];
	for (int i = 0; i < n; i++)
		matrix_fA[i] = new float[n];

	matrix_fB = new float*[n];
	for (int i = 0; i < n; i++)
		matrix_fB[i] = new float[n];

	matrix_fC = new float*[n];
	for (int i = 0; i < n; i++)
		matrix_fC[i] = new float[n];

	Initalize_Values(matrix_A, n); 										Initalize_Values(matrix_fA, n);
	Initalize_Values(matrix_B, n); 										Initalize_Values(matrix_fB, n);

#ifdef debug_display	
	cout << "Matrix A is: ";	Display(matrix_A, n); 						cout << "Matrix for floating A is: ";	Display(matrix_fA, n);
	cout << "Matrix B is: ";	Display(matrix_B, n); 						cout << "Matrix for floating B is: ";	Display(matrix_fB, n);
#endif

	d_time = omp_get_wtime();
	Matrix_Multiply_Serial(matrix_A, matrix_B, matrix_C, n);
#ifdef debug_display					
	cout << "Serial Result for double (Matrix C) is: "; 	Display(matrix_C, n);
#endif		
	d_time = omp_get_wtime() - d_time;

	f_time = omp_get_wtime();
	Matrix_Multiply_Serial(matrix_fA, matrix_fB, matrix_fC, n);
#ifdef debug_display
	cout << "Serial Result for floating (Matrix C) is: "; 	Display(matrix_fC, n);
#endif
	f_time = omp_get_wtime() - f_time;


	parallel_d_time = omp_get_wtime();
	Matrix_Multiply_Parallel(matrix_A, matrix_B, matrix_C, n);
#ifdef debug_display					
	cout << "Parallel Result for double (Matrix C) is: "; 	Display(matrix_C, n);
#endif		
	parallel_d_time = omp_get_wtime() - parallel_d_time;

	parallel_f_time = omp_get_wtime();
	Matrix_Multiply_Parallel(matrix_fA, matrix_fB, matrix_fC, n);
#ifdef debug_display					
	cout << "Parallel Result for floating (Matrix C) is: "; 	Display(matrix_fC, n);
#endif		
	parallel_f_time = omp_get_wtime() - parallel_f_time;


	cout << "\n*****************************************************************************************************************\n";
	cout << "For a Square Matrix with dimension (N)=" << n << endl;
	printf("The time for serial matrix multiplication for double operation is \t: %f", d_time);
	cout << endl;
	printf("The time for serial matrix multiplication for floating operation is \t: %f", f_time);
	cout << endl << endl;
	cout << "For " << NUM_THREADS << " threads:" << endl;
	printf("The time for parallel matrix multiplication for double operation is \t: %f", parallel_d_time);
	cout << endl;
	printf("The time for parallel matrix multiplication for floating operation is \t: %f", parallel_f_time);
	cout << "\n*****************************************************************************************************************\n";

	return 0;
}