#include <stdio.h>
#include <math.h>  //pow�� math.h�� �ִ� �Լ���

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
		printf("\n\n"); //���ٶ�� ����ؼ� �ٸ� ���ڸ� �־ �ݺ������� �� �� �ְ� ��

		//Error bound 10^-8�̸������ض�	
		//3pairs of points (-10, -9.9) , (-0.1, -0.2), (10, 9.9)

		printf("ù ��° �������� �Է��Ͻÿ�");
		scanf_s("%lf", &x_1);

		printf("�� ��° �������� �Է��Ͻÿ�");
		scanf_s("%lf", &x_2);

		while (1) {

			f_old = func(x_1);
			f_new = func(x_2);

			slope = (x_2 - x_1) / (func(x_2) - func(x_1));
			// Slope�� �ȹٲٰ� ��� �����ϰ� �س�����.

			x_3 = x_2 - slope * func(x_2);//���ο� x������ ���ϴ� ������ �ڵ�� ������ ��

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