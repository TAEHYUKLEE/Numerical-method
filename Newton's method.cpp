#include <stdio.h>
#include <math.h>  //pow�� math.h�� �ִ� �Լ���

double func(double x) {

	double y;
	double y_prime;
	double ratio;

	y = pow(x, 5) - 9 * pow(x, 4) - pow(x, 3) + 17 * pow(x, 2) - 8 * x - 8;
	//y�� ���� �̺� term�� �˾ƾ��Ѵ�. 
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
		printf("\n\n"); //���ٶ�� ����ؼ� �ٸ� ���ڸ� �־ �ݺ������� �� �� �ְ� ��

		//Error bound 10^-8�̸������ض�	
		//3���� ���ؼ� -10, 0.1, 10

		printf("�������� �Է��Ͻÿ�");
		scanf_s("%lf", &x_old);

		while (1) {

			ratio = func(x_old);

			x_new = x_old - ratio; //���ο� x_new�� ���ϴ� ����
			epsil = fabs(x_new - x_old);
			x_old = x_new;

			printf("x_new: %f\n", x_new);
			printf("x_old: %f\n", x_old);   //Initial condition�� 0�϶��� �ּ��� Ǯ�� Print�غ��ÿ�.
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