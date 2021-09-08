#include <stdio.h>
#include <math.h>

double A[4][4] = { { 60, 544, 131, 323 }, {8, 66.3, 4, 2},{ 8, 666, 4744, 1 },{ 665656, 7, 5, 367856865 } };
double B[4][4] = { { 8370, 9.3, 6.2, 4.3},{ 5424.1, 622, 43.2, 3 }, { 1132, 4444.59, 2, 3 },{ 5323.6, 44, 79.47, 9} };
double C[4][4];
double Cin[4][8] = { { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 } ,{ 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 } ,
					{ 0.0, 0.0, 0.0, 0.0 ,0.0, 0.0, 1.0, 0.0} ,{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0  } }; // 나중에 inverse가 될 행렬
double C_1[4][4];
double I[4][4];

int main(void) {

	int i, j, k;
	int n = 4;
	double sum = 0;
	double med = 0;
	double f = 0;


	//1번문제 A행렬 X B행렬 = C로 나타내기
	for (k = 0; k < n; k++) {//C Matrix의 열부터 채워나간다. (k는 열)

		for (i = 0; i < n; i++) {

			for (j = 0; j < n; j++) {

				med = A[i][j] * B[j][k];
				sum = med + sum;

				med = 0;
			}

			C[i][k] = sum;
			sum = 0; //초기화 시켜주지 않으면 계속해서 누적됨
		}
	}

	//Aumgented matrix form으로 만들기
	for (i = 0; i < 4; i++)

		for (j = 0; j < 4; j++) {

			Cin[i][j] = C[i][j];

		}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) {
			printf("C[%d][%d]: %f\n", i, j, C[i][j]);
		}
	} //확인함

		   
	/////////////////////////////////////// Inverse Matrix  Gauss Jordan Elimination으로 해보자//////////////////////////////////////
	
	for (j = 0; j < n;j++) //J Coulum 고정 한 칼럼씩 내려가면서 0으로 만든다. 
	{
		for (i = 0;i < n;i++) //위의 j에서 렬을 고정시키고 i행을 바꿔가면서 내려가면서 0으로 만든다.
		{
			if (i != j) //Diagonal외의 모든 element들을 0으로 만들기 위한 조건문 
			{
				f = Cin[i][j] / Cin[j][j]; //Diagonal을 기준으로 Factor를 만들어 0으로 제거해 나감 
			}
			for (k = 0; k < 2*n; k++)  //i, j는 고정되어 있으므로 전체 Row operation할 변수가 필요함 그게 k임 (
			{                    //k로 렬을 옮겨다니면서 Row operation을 해준다. 

				Cin[i][k] = Cin[i][k] - Cin[j][k] * f; //Cin[j][j]*f라고 처음에 표기함  -->  처음에 Diagonal을 생각해서 했지만, 여기서는 모든 열에 대한 계산값이므로 [j][k]가 맞다. 
			}
		}
	}

for (i = 0; i < n; i++) {

	for (k = 4; k < 2*n; k++)
	{
		Cin[i][k] = Cin[i][k] / Cin[i][i]; //invers matrix를 Diagonal format으로 나눠줌으로써 마무리한다.

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
		//역행렬 error아닌거 찾는게 더 힘드네...

	
///////////////////////////////////////////////// C Matrix X C_in Matrix = I matrix 인지 확인해라 //////////////////////////////////////////////
	
//Augmented form인 Cin[4][8]을 다시 [4][4]로 바꿔서 

	double a;

	for (i = 0; i < n; i++)

		for (j = 4; j < 2*n; j++) {

			 a= Cin[i][j]; //C_1는 4X4 C의 Inverse matrix

			 for (k = 0; k < n; k++) {

				 if ((k + 4) == j) {
					 C_1[i][k] = a;
				 }
			 }	
		}

	//역행렬 잘 들어갔나 Print해보기
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) {
			printf("C_1[%d][%d]: %f\n", i, j, C_1[i][j]);
		}
	}
	//C의 역행렬 C_1을 따로 뽑아냄.



	//앞에서 Product한걸 그대로 가져와서 C X C_1을 해봐야함
	
	
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