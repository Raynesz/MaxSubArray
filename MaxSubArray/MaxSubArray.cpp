#include "stdafx.h"
#include <iostream>
#include "time.h"

#define sizeA 4000            //sizes of the arrays
#define sizeB 8000

void generateArrays(int seed, int a[sizeA], int b[sizeB]);
void printArrays(int a[sizeA], int b[sizeB]);
void maxSubarray1(int a[sizeA], int b[sizeB], double times[2][2]);
void maxSubarray2(int a[sizeA], int b[sizeB], double times[2][2]);
void printTimes(double times[2][2]);

using namespace std;

int main()
{
	int seed, a[sizeA], b[sizeB];
	double times[2][2];

	//cout << "Seed: " << endl;
	//cin >> seed;
	seed = 322172966410;                  //random seed

	generateArrays(seed, a, b);     //create arrays
	printArrays(a, b);              //print them

	maxSubarray1(a, b, times);      //algorithm1: Brute Force
	maxSubarray2(a, b, times);      //algorithm2: Kadane's algorithm
	
	printTimes(times);

	system("pause");
    return 0;
}

void generateArrays(int seed, int a[sizeA], int b[sizeB]) {
	srand(seed);
	int floor = -35, ceiling = 35, range = (ceiling - floor);

	for (int i = 0; i < sizeA; i++) {
		a[i] = floor + int((range * rand()) / (RAND_MAX + 1.0));     //fill arrays with values ranging between -35 and 35
	}
		
	for (int i = 0; i < sizeB; i++) {
		b[i] = floor + int((range * rand()) / (RAND_MAX + 1.0));
	}
}

void printArrays(int a[sizeA], int b [sizeB]) {
	cout << "A[ "<< sizeA << "] = [";
	for (int i=0; i<sizeA; i++) {
		cout << a[i] << " ";
	}
	cout << "]" << endl;

	cout << "B[ " << sizeB << "] = [";
	for (int i=0; i<sizeB; i++) {
		cout << b[i] << " ";
		if (i == 69) cout << endl;
	}
	cout << "]" << endl;
}

void maxSubarray1(int a[sizeA], int b[sizeB], double times[2][2]) {
	                            //BRUTE FORCE for array A
	clock_t begin = clock();                                     //clock start
	int maxSumSoFar = 0;
	int maxISoFar = 0;
	int maxJSoFar = -1;
	for (int i = 0; i<sizeA; i++) {
		int sum = 0;
		for (int j = i; j<sizeA; j++) {
			sum += a[j];
			if (sum>maxSumSoFar) {
				maxSumSoFar = sum;
				maxISoFar = i;
				maxJSoFar = j;
			}
		}
	}
	clock_t end = clock();                                      //clock stop
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	times[0][0] = time_spent;
	cout << "Algorithm 1, Array A Max Sum = " << maxSumSoFar << endl;
	                           //BRUTE FORCE for array B
	begin = clock();
	maxSumSoFar = 0;
	maxISoFar = 0;
	maxJSoFar = -1;
	for (int i = 0; i<sizeB; i++) {
		int sum = 0;
		for (int j = i; j<sizeB; j++) {
			sum += b[j];
			if (sum>maxSumSoFar) {
				maxSumSoFar = sum;
				maxISoFar = i;
				maxJSoFar = j;
			}
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	times[0][1] = time_spent;
	cout << "Algorithm 1, Array B Max Sum = " << maxSumSoFar << endl;
}

void maxSubarray2(int a[sizeA], int b[sizeB], double times[2][2]) {
								//KADANE'S array A
	clock_t begin = clock();
	int max_so_far = INT_MIN, max_ending_here = 0,
		start = 0, iend = 0, s = 0;
	for (int i = 0; i< sizeA; i++)
	{
		max_ending_here += a[i];

		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			start = s;
			iend = i;
		}
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			s = i + 1;
		}
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	times[1][0] = time_spent;
	cout << "Algorithm 2, Array A Max Sum = " << max_so_far << endl;
	cout << "Starting index " << start
		<< endl << "Ending index " << iend << endl;
	                           //KADANE'S array B
	begin = clock();
	max_so_far = INT_MIN, max_ending_here = 0,
		start = 0, iend = 0, s = 0;
	for (int i = 0; i< sizeB; i++)
	{
		max_ending_here += b[i];

		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			start = s;
			iend = i;
		}
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			s = i + 1;
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	times[1][1] = time_spent;
	cout << "Algorithm 2, Array B Max Sum = " << max_so_far << endl;
	cout << "Starting index " << start
		<< endl << "Ending index " << iend << endl;
}

void printTimes(double times[2][2]) {
	for (int i = 0; i < 2; i++) {
		cout << "Algorithm" << i+1 << ": A = " << times[i][0] << "seconds, " << "B = " << times[i][1] << "seconds" << endl;
	}
}