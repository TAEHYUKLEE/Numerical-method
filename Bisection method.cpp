#include <stdio.h>
#include <math.h>  //pow�� math.h�� �ִ� �Լ���


//�����Լ��� '�ĺ��ڸ� ã�� �� �����ϴ�' ������ ��� ���� �������� Ȯ���� �� ��.
//Classó�� main�Լ����� �տ� �����Լ��� ���ؼ� �˷���� main�Լ����� �ĺ� �� �� �ִ�.
double func(double x) {

	double y;
	y = pow(x, 5) - 9 * pow(x, 4) - pow(x, 3) + 17 * pow(x, 2) - 8 * x - 8;

	return y;
}

int main(void) {

	double x_1, x_2;
	double x_3 =0;
	double a, b;
	double epsil = 0;
	double solution;
	int count=0;

	while (1) { 
		printf("\n\n"); //���� �ٰ�

		//���� ������ ����ؼ� �����ظ� �������� ���Ҽ� �ְ���
		//Error bound 10^-8�̸������ض�	

		//1�� ���� [-10, -1]
		//2�� ���� [-1, 0]
		//3�� ���� [0, 10]

		//������ ���� �� �� ���������� �Ϲ�ȭ��Ű�� ���� scanf�� �����
		printf("������ ù ���ڸ� �Է��ϼ���");
		scanf_s("%lf", &x_1);

		printf("������ �� ��° ���ڸ� �Է��ϼ���");
		scanf_s("%lf", &x_2);
		//scanf_s�� scanf�� �Ҿ����Ͽ� ���Դٰ� �˷��� �ִ� str����Ҷ��� �ڿ� sizeof�����ڸ� �ٿ����Ѵ�

		while (1) {

			a = func(x_1);
			b = func(x_2);

			//printf("a: %f", a);
			//printf("b: %f", b);

			if (a * b < 0) {

				x_3 = (x_1 + x_2) / 2;

				/*printf("x_3: %lf\n", x_3);
				printf("func(x_3) * func(x_1): %f\n", func(x_3) * func(x_1));
				printf("func(x_3) * func(x_2): %f\n", func(x_3) * func(x_2));*/

				if (func(x_3) * func(x_1) < 0) {
					//printf("yes1\n");
					x_2 = x_3;
				}
				else if (func(x_3) * func(x_2) < 0) {
					//printf("yes2\n");
					x_1 = x_3;
				}

			}
			/*printf("x_1: %lf\n", x_1);
			printf("f(x_1): %lf\n",a);
			printf("\n");
			printf("x_2: %lf\n", x_2);
			printf("f(x_2): %lf\n", b);
			printf("\n");*/

			epsil = fabs(x_1 - x_2);

			//printf("epsil: %f\n", epsil);
			count = count + 1;

			if (epsil < pow(10, -8)) {
				break;
			}
			//fabs double�� ���� ���� �������� �׳� abs (integer)�� �����Ұ�


		}

		//printf("epsil: %lf\n", epsil);

		solution = (x_1 + x_2) / 2;
		printf("solution: %lf\n", solution);
		printf("count: %d \n", count);
	}
		
	return 0;
}
/*Bisection method �ణ ������� Root locusó�� �� �κи� ���� �ְ� �������ΰ� ������ ����. ���� � ������ ���ؼ� ������ ��������
����ϴ°� ������. ������ �ظ� ã���� �� ������ �������� ������ �ǹ̰� ����.*/