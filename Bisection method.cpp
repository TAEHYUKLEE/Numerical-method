#include <stdio.h>
#include <math.h>  //pow는 math.h에 있는 함수임


//지역함수에 '식별자를 찾을 수 없습니다' 오류가 뜬다 무슨 오류일지 확인해 볼 것.
//Class처럼 main함수에서 앞에 지역함수에 대해서 알려줘야 main함수에서 식별 할 수 있다.
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
		printf("\n\n"); //두줄 뛰고

		//무한 루프로 계속해서 다음해를 연속으로 구할수 있게함
		//Error bound 10^-8미만으로해라	

		//1번 구간 [-10, -1]
		//2번 구간 [-1, 0]
		//3번 구간 [0, 10]

		//구간에 대해 좀 더 범용적으로 일반화시키기 위해 scanf를 사용함
		printf("구간의 첫 숫자를 입력하세요");
		scanf_s("%lf", &x_1);

		printf("구간의 두 번째 숫자를 입력하세요");
		scanf_s("%lf", &x_2);
		//scanf_s는 scanf가 불안정하여 나왔다고만 알려져 있다 str사용할때는 뒤에 sizeof연산자를 붙여야한다

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
			//fabs double에 대한 값을 절댓값으로 그냥 abs (integer)와 구분할것


		}

		//printf("epsil: %lf\n", epsil);

		solution = (x_1 + x_2) / 2;
		printf("solution: %lf\n", solution);
		printf("count: %d \n", count);
	}
		
	return 0;
}
/*Bisection method 약간 기시제의 Root locus처럼 한 부분만 볼수 있고 전반적인걸 볼수가 없다. 내가 어떤 지역에 대해서 관심이 있을때만
사용하는게 좋을듯. 무조건 해를 찾지만 그 구간을 정해주지 않으면 의미가 없다.*/