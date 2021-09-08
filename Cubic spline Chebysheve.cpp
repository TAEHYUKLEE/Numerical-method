#include <stdio.h>
#define _USE_MATH_DEFINES //it is included in math.h
#include <math.h>

double x_1, x_2, h, x, y, n, factor;
double u[11], a[10], b[10], c[10], d[10];
int i, j, k, I, Num;
double F[10], g_prime[11], f[11];
double g[9];

double func(double x) {

	double y;

	y = 1 / (1 + 16 * pow(x, 2));

	return y;
}

double Chebyshev(double I, double Num) { //node 작업

	double n;

	n = cos((2 * I + 1) / (2 * Num + 2) * M_PI);

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

	printf("put your x number at which you are interested:");
	scanf_s("%lf", &x);

	for (i = 0; i <= I; i++) { // nodes x[i]
		u[i] = Chebyshev(i, Num);
		//printf("u[%d]: %lf \n", i, u[i]);
	}

	for (i = 0; i <= I; i++) { //Lagrange polynomial 

		f[i] = func(u[i]);
		printf("Each Data point is u[%d]: %lf, f[%d]: %lf \n", i, u[i], i, f[i]);
	}
	
	////////////////////////////////////////  Formation of Tri Diagonal Matrix  /////////////////////////////////////////////

	for (i = 0; i < I - 1; i++) { //2행부터 a,b,c,y2

		a[i] = (u[i + 1] - u[i]) / (u[i + 2] - u[i + 1]);

		b[i] = 2 * (u[i + 2] - u[i]) / (u[i + 2] - u[i + 1]);

		if (i != n - 2) {
			c[i] = 1;
		}

		d[i] = 6 * ((f[i + 2] - f[i + 1]) / pow((u[i + 2] - u[i + 1]), 2) -
			(f[i + 1] - f[i]) / ((u[i + 2] - u[i + 1]) * (u[i + 1] - u[i])));

		printf("a[%d]: %f, b[%d]: %f, c[%d]: %f, d[%d]: %f\n", i, a[i], i, b[i], i, c[i], i, d[i]);
	}

	/////////////////////////  TDMA  ////////////////////////////

	for (i = 1; i < I - 1; i++) {

		factor = a[i] / b[i - 1]; //a,b,c (b/a)
		a[i] = a[i] - factor * b[i - 1]; //a term 사실 필요없음
		b[i] = b[i] - factor * c[i - 1]; //b term
		d[i] = d[i] - factor * d[i - 1]; // d term

		printf("a[%d]: %f, b[%d]: %f, c[%d]: %f, d[%d]: %f\n", i, a[i], i, b[i], i, c[i], i, d[i]);
	}

	//Initial condition
	g_prime[0] = 0;
	g_prime[10] = 0;
	g[8] = d[8] / b[8];//g[8] = d[8] / b[8];
	g_prime[9] = g[8];

	for (i = I - 3; i >= 0; i--) {

		g[i] = (d[i] - c[i] * g[i + 1]) / b[i];

		g_prime[i + 1] = g[i];
	}

	for (i = 0; i < I + 1; i++) {

		printf("g_prime[%d]: %f\n", i, g_prime[i]);
	}

	// Last step, Section of Fi(x) should be defined

	for (i = 0; i < I; i++) {

		double del = u[i + 1] - u[i];

		F[i] = (g_prime[i] / 6) * (pow((u[i + 1] - x), 3) / del - (del * (u[i + 1] - x))) +
			(g_prime[i + 1] / 6) * (pow((x - u[i]), 3) / del - (del * (x - u[i]))) +
			f[i] * ((u[i + 1] - x) / del) + f[i + 1] * (x - u[i]) / del;
	}

	for (i = 0; i < I; i++) {
		{
			if (u[i] > x  &&  x > u[i + 1]) {
				printf("F[%d]: %lf\n", i, F[i]);
			}
		}
	}
	return 0;
}