#include <stdio.h>
#define _USE_MATH_DEFINES //it is included in math.h
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>

double x_1, x_2, n, x, med;
int i, j, k, I, Num;
double D[11], N[11], P[11], F[11], u[11];
double N_sum = 1;
double D_sum = 1; //Denominator, Numerator, Polynomial
double f = 0;

double func(double x) {

	double y;

	y = 1 / (1 + 16 * pow(x, 2));

	return y;
}

double Chebyshev(double I, double Num) { //node ÀÛ¾÷

	double n;

		n = cos((2 * I + 1) / (2 * Num +2)* M_PI);
	
		return n;
}

int main(void) {

	printf("put in your first number for the interval:");
	scanf_s("%lf", &x_1);
	printf("put in your second number for the interval:");
	scanf_s("%lf", &x_2);
	
	printf("put in numbers of N you want: (Ex is N=10):");
	scanf_s("%d", &Num);
	printf("put in numbers of nodes (I) you want I: (Ex is I=10)");
	scanf_s("%d", &I);

	while (1) {
		printf("put your x number at which you are interested:");
		scanf_s("%lf", &x);

		for (i = 0; i <= I; i++) { // nodes x[i]
			u[i] = Chebyshev(i, Num);
			printf("u[%d]: %lf \n", i, u[i]);
		}

		for (i = 0; i <= I; i++) { //Lagrange polynomial 

			F[i] = func(u[i]);
			printf("Each Data point is F[%d]: %lf \n", i, F[i]);
		}

		for (i = 0; i <= I; i++) {

			for (j = 0; j <= I; j++) {

				if (i != j) {
					N[j] = x - u[j];
					D[j] = (u[i] - u[j]);

					N_sum = N_sum * N[j];
					D_sum = D_sum * D[j];
				}
			}

			P[i] = N_sum / D_sum;
			printf("P[%d]:%lf \n", i, P[i]);

			N_sum = 1;
			D_sum = 1;
		}
		//Each Polynomial function(s) are found above loop

		//Lagrange Polynomial 


		for (i = 0; i <= I; i++) {

			med = F[i] * P[i];

			f = f + med;
		}

		printf("Lagrange polynomial: %lf\n", f);

		f = 0;
	}
	return 0;
}