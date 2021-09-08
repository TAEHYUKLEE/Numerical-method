#include <stdio.h>
#include <math.h>

double x_1, x_2, h, x, y,n, factor;
double u[11], a[9], b[9], c[9];
int i, j, k;
double A[9][10] = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0} }; //Gauss elimination 
double g[11], f[11], F[10];

double func(double x) {

	double y;

	y = 1 / (1 + 16 * pow(x, 2));

	return y;
}

int main(void) {

	printf("put your first number for the interval:");
	scanf_s("%lf", &x_1);

	printf("put your second number for the interval:");
	scanf_s("%lf", &x_2);


	printf("put your uniform nodes h:");
	scanf_s("%lf", &h);

	printf("put your x number at which you are interested:");
	scanf_s("%lf", &x);

	n = ((x_2 - x_1) / h); 
	printf("nodes numbers:%lf \n", n+1);
	
	for (i = 0; i <= n; i++) { //Lagrange polynomial

		u[i] = x_1 +((x_2 - x_1) / n) * (i);
		f[i] = func(u[i]);
		printf("Each Data point is u[%d]: %lf \n", i, u[i]);
		printf("Each Data point is f[%d]: %lf \n", i, f[i]);

	}
	// Dataset is complete

	//Cubic spline function, Pointer must be used for localization of Cubic spline functino, do it later
	
	////////////////////////////////////////  Formation of Tri Diagonal Matrix  /////////////////////////////////////////////
	for (i = 0; i < n-1; i++) { //2วเบฮลอ a,b,c,y2

		for (j = 0; j < n-1; j++) {

			if (i == j) {
				
				if (i != 0) {
					a[j+1] = (u[j+1] - u[j]) / (u[j + 2] - u[j+1]);
				}
				b[j+1] = 2 * (u[j + 2] - u[j]) / (u[j + 2] - u[j+1]);
				
				if (i != 8) {
					c[j+1] = 1;
				}
				//at last row, we should put only two numbers

				y = 6 * ((f[j + 2] - f[j+1]) / pow((u[j + 2] - u[j+1]), 2) - (f[j+1] - f[j]) / ((u[j + 2] - u[j+1]) * (u[j+1] - u[j])));
				
				if (i != 0) {
				A[i][j - 1] = a[j+1];}
				A[i][j] = b[j+1];
				A[i][j + 1] = c[j+1];
				A[i][9] = y;

				//at first, j < n-1 was set to make decision for index but it is not right it would be overlapped by A[i][9]
				//printf("%d\n", j);

			}
		}
	}
	
	/*for (i = 0; i < 9; i++) {

		for (j = 0; j < 10; j++) {
			printf("A[%d][%d]: %f\n", i, j, A[i][j]);

		}
	}*/

	/////////////////////////  TDMA  ////////////////////////////

	for (i = 1; i < n; i++) {

		for (j = 0; j < n; j++) {

			if(i==j){
				factor = A[i][j - 1] / A[i - 1][j - 1]; //a,b,c (b/a)
				A[i][j - 1] = A[i][j - 1] - factor * A[i - 1][j - 1]; //a term
				A[i][j] = A[i][j] - factor * A[i - 1][j]; //b term
				A[i][9] = A[i][9] - factor * A[i][9]; // d term
			}
		}

	}

	//Initial condition
	g[0] = 0;
	g[10] = 0;

	g[9] = A[8][9] / A[8][8];


	for (i = n-2; i >=0; i--) {

		for (j = 0; j < n; j++) {

			if (i == j) {
				g[i+1] = (A[i][9] - A[i][j + 1] * g[i + 2]) / A[i][j];
			}
		}
	}

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 10; j++) {
			printf("A[%d][%d]: %f\n", i, j, A[i][j]);

		}
	}

	for (i = 0; i <= 10; i++) {
		printf("g[%d]: %lf\n", i, g[i]);
	}
	// 11 points are founded (double prime of g)

	// Last step, Section of Fi(x) should be defined

	for (i = 0; i < n ; i++) {
			F[i] = g[i]/6*(pow( (u[i+1] - x), 3)/(u[i+1]-u[i]) - (u[i + 1] - u[i])*(u[i+1] - x)) +
			g[i+1] / 6 * (pow( (x - u[i]) , 3) / (u[i + 1] - u[i]) - (u[i + 1] - u[i]) * ( x - u[i])) + 
			f[i]*((u[i + 1] - x)/ u[i + 1] - u[i]) + f[i+1]*((x-u[i])/(u[i + 1] - u[i]));
	}
		
	for (i = 0; i < n; i++) {
		{
			printf("F[%d]: %lf\n", i, F[i]);
		}
	}

	return 0;
}