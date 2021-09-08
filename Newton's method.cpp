#include <stdio.h>
#include <math.h>  //pow는 math.h에 있는 함수임

double func(double x) {

	double y;
	double y_prime;
	double ratio;

	y = pow(x, 5) - 9 * pow(x, 4) - pow(x, 3) + 17 * pow(x, 2) - 8 * x - 8;
	//y에 대한 미분 term을 알아야한다. 
	y_prime = 5*pow(x, 4) - 36 * pow(x, 3) - 3*pow(x, 2) + 34 * x - 8;
	
	ratio = y / y_prime;

	return ratio;
}

int main(void) {

	double x_old;
	double x_new;
	double ratio;
	double epsil = 0;
	double solution;
	int count = 0;

	while (1) {
		printf("\n\n"); //두줄띄고 계속해서 다른 숫자를 넣어서 반복적으로 할 수 있게 함

		//Error bound 10^-8미만으로해라	
		//3점에 대해서 -10, 0.1, 10

		printf("시작점을 입력하시오");
		scanf_s("%lf", &x_old);

		while (1) {

			ratio = func(x_old);

			x_new = x_old - ratio; //새로운 x_new를 구하는 수식
			epsil = fabs(x_new - x_old);
			x_old = x_new;

			printf("x_new: %f\n", x_new);
			printf("x_old: %f\n", x_old);   //Initial condition이 0일때만 주석을 풀고 Print해보시오.
			count = count + 1;
			
			if (epsil < pow(10, -8)) {
				break;
			}
			
		}

		//printf("epsil: %lf", epsil);

		solution = x_new ;
		printf("solution: %lf\n", solution);
		printf("count: %d \n", count);

	}

	return 0;
}