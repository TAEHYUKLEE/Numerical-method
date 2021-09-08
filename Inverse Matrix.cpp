#include <stdio.h>
#include <math.h>

double A[4][4] = { { 60, 544, 131, 323 }, {8, 66.3, 4, 2},{ 8, 666, 4744, 1 },{ 665656, 7, 5, 367856865 } };
double B[4][4] = { { 8370, 9.3, 6.2, 4.3},{ 5424.1, 622, 43.2, 3 }, { 1132, 4444.59, 2, 3 },{ 5323.6, 44, 79.47, 9} };
double C[4][4];
double Cin[4][8] = { { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 } ,{ 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 } ,
					{ 0.0, 0.0, 0.0, 0.0 ,0.0, 0.0, 1.0, 0.0} ,{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0  } }; // ���߿� inverse�� �� ���
double C_1[4][4];
double I[4][4];

int main(void) {

	int i, j, k;
	int n = 4;
	double sum = 0;
	double med = 0;
	double f = 0;


	//1������ A��� X B��� = C�� ��Ÿ����
	for (k = 0; k < n; k++) {//C Matrix�� ������ ä��������. (k�� ��)

		for (i = 0; i < n; i++) {

			for (j = 0; j < n; j++) {

				med = A[i][j] * B[j][k];
				sum = med + sum;

				med = 0;
			}

			C[i][k] = sum;
			sum = 0; //�ʱ�ȭ �������� ������ ����ؼ� ������
		}
	}

	//Aumgented matrix form���� �����
	for (i = 0; i < 4; i++)

		for (j = 0; j < 4; j++) {

			Cin[i][j] = C[i][j];

		}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) {
			printf("C[%d][%d]: %f\n", i, j, C[i][j]);
		}
	} //Ȯ����

		   
	/////////////////////////////////////// Inverse Matrix  Gauss Jordan Elimination���� �غ���//////////////////////////////////////
	
	for (j = 0; j < n;j++) //J Coulum ���� �� Į���� �������鼭 0���� �����. 
	{
		for (i = 0;i < n;i++) //���� j���� ���� ������Ű�� i���� �ٲ㰡�鼭 �������鼭 0���� �����.
		{
			if (i != j) //Diagonal���� ��� element���� 0���� ����� ���� ���ǹ� 
			{
				f = Cin[i][j] / Cin[j][j]; //Diagonal�� �������� Factor�� ����� 0���� ������ ���� 
			}
			for (k = 0; k < 2*n; k++)  //i, j�� �����Ǿ� �����Ƿ� ��ü Row operation�� ������ �ʿ��� �װ� k�� (
			{                    //k�� ���� �Űܴٴϸ鼭 Row operation�� ���ش�. 

				Cin[i][k] = Cin[i][k] - Cin[j][k] * f; //Cin[j][j]*f��� ó���� ǥ����  -->  ó���� Diagonal�� �����ؼ� ������, ���⼭�� ��� ���� ���� ��갪�̹Ƿ� [j][k]�� �´�. 
			}
		}
	}

for (i = 0; i < n; i++) {

	for (k = 4; k < 2*n; k++)
	{
		Cin[i][k] = Cin[i][k] / Cin[i][i]; //invers matrix�� Diagonal format���� ���������ν� �������Ѵ�.

	}
	Cin[i][i] = Cin[i][i] / Cin[i][i];

}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 2 * n; j++) {
			printf("Cin[%d][%d]: %f", i, j ,Cin[i][j]);
		}
		printf("\n");
	}
		//����� error�ƴѰ� ã�°� �� �����...

	
///////////////////////////////////////////////// C Matrix X C_in Matrix = I matrix ���� Ȯ���ض� //////////////////////////////////////////////
	
//Augmented form�� Cin[4][8]�� �ٽ� [4][4]�� �ٲ㼭 

	double a;

	for (i = 0; i < n; i++)

		for (j = 4; j < 2*n; j++) {

			 a= Cin[i][j]; //C_1�� 4X4 C�� Inverse matrix

			 for (k = 0; k < n; k++) {

				 if ((k + 4) == j) {
					 C_1[i][k] = a;
				 }
			 }	
		}

	//����� �� ���� Print�غ���
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) {
			printf("C_1[%d][%d]: %f\n", i, j, C_1[i][j]);
		}
	}
	//C�� ����� C_1�� ���� �̾Ƴ�.



	//�տ��� Product�Ѱ� �״�� �����ͼ� C X C_1�� �غ�����
	
	
	for (k = 0; k < n; k++) {

		for (i = 0; i < n; i++) {

			for (j = 0; j < n; j++) {

				med = C[i][j] * C_1[j][k];
				sum = med + sum;

				med = 0;
			}

			I[i][k] = sum;
			sum = 0;
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) {
			printf("I[%d][%d]: %f\n", i, j, I[i][j]);
		}
	}

	return 0;
}