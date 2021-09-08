#include <stdio.h>
#include <math.h>  //pow는 math.h에 있는 함수임

double func(double x) {

	double y;

	y = pow(x, 5) - 9 * pow(x, 4) - pow(x, 3) + 17 * pow(x, 2) - 8 * x - 8;

	return y;
}


int main(void) {

	double x_1, x_2, x_3;
	double f_old, f_new, slope;
	double epsil = 0;
	double solution;
	int count = 0;

	while (1) {
		printf("\n\n"); //두줄띄고 계속해서 다른 숫자를 넣어서 반복적으로 할 수 있게 함

		//Error bound 10^-8미만으로해라	
		//3pairs of points (-10, -9.9) , (-0.1, -0.2), (10, 9.9)

		printf("첫 번째 시작점을 입력하시오");
		scanf_s("%lf", &x_1);

		printf("두 번째 시작점을 입력하시오");
		scanf_s("%lf", &x_2);

		while (1) {

			f_old = func(x_1);
			f_new = func(x_2);

			slope = (x_2 - x_1) / (func(x_2) - func(x_1));
			// Slope을 안바꾸고 계속 일정하게 해놨었다.

			x_3 = x_2 - slope * func(x_2);//새로운 x지점을 구하는 수식을 코드로 구현한 것

			epsil = fabs(x_3- x_2);

			x_1 = x_2;
			x_2 = x_3;
			
			count = count + 1;

			if (epsil < pow(10, -8)) {
				break;
			}
;

		}

		solution = x_3;
		printf("solution: %lf\n", solution);
		printf("count: %d \n", count);

	}

	return 0;
}