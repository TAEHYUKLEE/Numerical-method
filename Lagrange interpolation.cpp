#include <stdio.h>
#include <math.h>

double x_1, x_2, h, n, x, med, f;
double u[11];
int i, j, k;
double F[11] ;
double D[11], N[11], P[11];
double N_sum = 1;
double D_sum = 1; //Denominator, Numerator, Polynomial
//오류가 떴음 double*F 외부 기호를 확인할 수 없습니다. 


double func (double x) {

	double y;

	y = 1 / (1 + 16 * pow(x, 2));

	return y;
}

int main(void) {
	
	printf("put your first number for the interval:");
	scanf_s("%lf" , &x_1);
	
	printf("put your second number for the interval:");
	scanf_s("%lf", &x_2);

	//scanf_s쓸때 조심해야 하는 것 "%lf"를 "%lf " 중간에 띄우면 안된다.
		
	printf("put your uniform nodes h:");
	scanf_s("%lf", &h);

	//FILE* pFile;
	//pFile = fopen("Lagrange data.txt", "w");

	while (1) {
		
		printf("put your x number at which you are interested:");
		scanf_s("%lf", &x);

		n = ((x_2 - x_1) / h); //not including left end point. so it would be degree of P(x)
								//technically nodes numbers are total interval nodes + 1 but at below for loop it add 1 automatically
		for (i = 0; i <= n; i++) { //Lagrange polynomial

			u[i] = x_1 + ((x_2 - x_1) / n) * (i);
			//printf("node x[%d] %lf", i, u[i]); printing each nodes numbers
			//printf("\n");

			F[i] = func(u[i]);
			printf("Each Data point is u[%d]: %lf , F[%d]: %lf \n", i, u[i], i, F[i]);

		}

		//Lagrange polynomial equation  (10 degrees polynomial)
		// already u[index] is declared as numbers of nodes

		for (i = 0; i <= n; i++) {

			for (j = 0; j <= n; j++) {

				if (i != j) {
					N[j] = x - u[j];
					D[j] = (u[i] - u[j]);

					//printf("x: %lf", x);
					//printf("x- u[%d]:%lf \n", j, x - u[j]);
					//printf("u[%d] - u[%d]:%lf \n", i, j, u[i] - u[j]);
					//printf("N[%d]:%lf \n",j, N[j]);
					//printf("D[%d]:%lf \n", j, D[j]);

					N_sum = N_sum * N[j];
					D_sum = D_sum * D[j];

				}

				//N_sum = N_sum * N[j]; 이렇게 밖에 놔두면 무엇이 문제인가?
				//D_sum = D_sum * D[j];

					//printf("N_sum is %lf \n", N_sum);
					//printf("D_sum is %lf \n", D_sum);
			}

			P[i] = N_sum / D_sum;
			printf("P[%d]:%lf \n", i, P[i]);
			//printf("D_sum:%lf \n", D_sum);

			N_sum = 1;
			D_sum = 1;
		}
		//Each Polynomial function(s) are found above loop

		f = 0;

		for (i = 0; i <= n; i++) {

			med = F[i] * P[i];

			f = f + med;
		}

		printf("Lagrange polynomial: %lf\n", f);
		//fprintf(pFile, "Name %d [%-10.10s]\n", n );

		f = 0;
	}
	//fclose(pFile);

		return 0;
	
}