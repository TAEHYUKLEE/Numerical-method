////////////////////////////////////////////// Second order Runge Kutta method ////////////////////////////////////////////////////
/*  x' = t + 2xt, x(0) = 0 */

#include <stdio.h>
#include <math.h>

double z[201], x[201], y[201], t[201],e[201], Dif[201];

int main(void)
{

	const char* s_output = "Output 0.01.csv";

	FILE* pfo;
		fopen_s(&pfo, s_output, "w");

	int n, i;
	double  f, f_1, f_2, f_3, t0, tn, h_Z, hh_Z, hhh_Z, h_1, h_X, hh_X, hhh_X, delt, L_1, L_2, Sum;
	t0 = 0;
	tn = 2;
	delt = 0.01;
	Sum = 0;
	n = (tn - t0)/delt; //delt 0.1로 하라고 하였으므 
	
	//초기값 설정 
	x[0] = 0.0;
	t[0] = 0.0;
	y[0] = 0.0;
	e[0] = 0.0;
	Dif[0] = 0.0;

	for (i = 0; i <= n; i++) {

		t[i] = delt * i;
 	}

	///////////////////////////// Exact Solution /////////////////////////////////////

	for (i = 0; i <= n; i++) {

		e[i] = (1.0) / (2.0) * (exp(pow(t[i], 2)) - 1);
		
	}

	///////////////////////////// 2th Order Runge Kutta ////////////////////////////////////
	for (i = 0;i <= n;i++)
	{

		f = (t[i] + 2 * x[i] * t[i]);
		h_X = x[i] + delt * f;
		f_1 = ((t[i] + delt) + 2 * h_X * (t[i] + delt));

		x[i + 1] = x[i] + delt * (1.0 / 2.0) * (f + f_1);

		//double a;
		//a = (1 / 2 * f + (1 / 2) * f_1); 이거 왜 0을 출력하지? 분자 (1.0)<--으로
		//a = delt*(f +  f_1)*1/2;
		//x[i + 1] = x[i] + a;
		//printf("a:%f \n",  a);

	}


	//여기까지해서 모든 값을 구하였다. 다음 출력 

	for (i = 0; i <= n; i++)
	{
		Dif[i] = pow((e[i] - x[i]),2);
		fprintf(pfo, " %lf, %10.9lf, %10.9lf\n", i * delt, x[i], e[i]);
		printf("Second order Runge Kutta: x[%f]=%f\n", i * delt, x[i]);

		Sum = Sum + Dif[i];
	}
	
		L_1 = sqrt(Sum);
		fprintf(pfo, "L2 norm of Second order of Runge Kutta: %10.9lf\n", L_1);

	f, f_1,f_2,f_3, h_X, hh_X, hhh_X, Sum = 0;

	//초기화 0까지 혹시 몰라서.
	for (i = 0; i < n; i++)
	{
		Dif[i] = 0;
		x[i] = 0;
	}


	///////////////////////////// 4th Order Runge Kutta ////////////////////////////////////

	for (i = 0;i <= n;i++)
	{

		//y값에 대해서 4th Runge Kutta 각 각 에 대해 풀이. 
		f = (t[i]  + 2 * x[i] * t[i]);
		h_X = x[i] + delt / (2.0) * f;
		f_1 = ((t[i] + delt / 2.0) + 2 * h_X * (t[i]+ delt/2.0));
		hh_X = x[i] + delt / (2.0) * f_1;
		f_2 = ((t[i] + delt/ 2.0) + 2 * hh_X * (t[i] + delt/ 2.0));
		hhh_X = x[i] + delt * f_2;
		f_3 = ((t[i]+delt) + 2 * hhh_X * (t[i]+delt));

		//printf("f: %f, f_1: %f, f_2: %f, f_3: %f\n", f, f_1, f_2, f_3);

		x[i + 1] = x[i] + delt * ((1.0/6.0)*f + (1.0/3.0) * f_1 + (1.0 / 3.0) * f_2 + (1.0 / 6.0) * f_3);

	}


	//여기까지해서 모든 값을 구하였다. 다음 출력 
	fprintf(pfo, "\n");
	fprintf(pfo, "4th Runge Kutta \n");

	for (i = 0; i <= n; i++)
	{
		Dif[i] = pow((e[i] - x[i]), 2);
		fprintf(pfo, " %lf, %10.9lf, %10.9lf\n", i * delt, x[i], e[i]);
		printf("Fourth order Runge Kutta: x[%f]=%f\n", i * delt, x[i]);

		Sum = Sum + Dif[i];
	}

	L_2 = sqrt(Sum);
	fprintf(pfo, "L2 norm of Second order of Runge Kutta: %10.15lf\n", L_2);

	fclose(pfo);
	   
	return 0;
}