#include <stdio.h>
#include <math.h>

#define  NN    4  // 2다항식이므로 계수가 3개 이므로 3X4행렬의 GAUSS JORDAN 행렬이 필요  : 열의 갯수
#define  NNp1  5  // 2다항식이므로 계수가 3개 이므로 3X4행렬의 GAUSS JORDAN 행렬이 필요  : 행의 갯수
#define  NoOfData   12  // 데이터의 갯수  
#define  NoOfInterval  100  // 적분을 위해 구간을 나누는 갯수

// 엑셀로 그려본 결과 3차함수를 그릴수 있다. 따라서 3차함수를 그려나가겠다. 
// row (행)의 수는 3개, 총 데이터 수는 10개 이다. 

double V[NoOfData] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};
double F[NoOfData] = {93, 87, 68, 55, 42, 37, 35, 39, 48, 53, 51, 39};

// 2차 방정식이면 (NN=3)   x의 4승 까지 계산 그러므로 상수부터는 5개 데이터 ( 2*(NN-1) + 1 ) 
//: 상수, 1차, 2차, 3차, 4차
// 3차 방정식이면 (NN=4)   x의 6승 까지 계산 그러므로 상수부터는 7개 데이터 ( 2*(NN-1) + 1 ) 
//: 상수, 1차, 2차, 3차, 4차, 5차, 6차  
// 4차 방정식이면 (NN=5)   x의 8승 까지 계산 그러므로 상수부터는 9개 데이터 ( 2*(NN-1) + 1 ) 
//: 상수, 1차, 2차, 3차, 4차, 5차, 6차, 7차, 8차   

double sum_m[ 2*(NN-1) + 1 ] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

double sum_r[NN]={0.0, 0.0, 0.0, 0.0};

double a[NN];

double A[NN][NNp1];

double Xstart       = 0.0;    // 적분구간 시작점
double Xstop        =1.1;    // 적분구간 끝나는 점
double Xdel         = (Xstop - Xstart) / NoOfInterval; // 각 적분구간의 X값


//// 매개변수가 행렬로 되어 있는데 정의하지 않고 사용하면 에러 발생함 ==> 위에서 double a[3]; 이 정의된 다음으(즉, 아래로) 이동  //************* 수정
// 함수의 원형  // 계수는 전역변수로 작성하였으므로 매개변수로 넘겨줄 필요 없음
double Trep ();   // 적분구간도 전역변수로 선언하였으므로 넘겨줄 필요 없다.
double Simp ();     

//[Curve fit 하고 Matrix까지 대입하는 것] 
int main(void)
{
	int l, j, k, i, n, m;
	double f;
	double sum_Trep, sum_simp;

	// 2차 방정식이면 (NN=3)   x의 4승  ( 2*(NN-1) ) 까지 계산 
	// 3차 방정식이면 (NN=4)   x의 6승  ( 2*(NN-1) ) 까지 계산 
	// 4차 방정식이면 (NN=5)   x의 8승  ( 2*(NN-1) ) 까지 계산 
for(l=0; l<=2*(NN-1); l++) // n, x, x^2, x^3, x^4 까지 시그마 값들을 구하기 위한 for문 (순서대로) 
	                 // 여기서 l 값은 급수를 나타낸다. 
	{
///for(k=0; k<=9; k++) //여기서의 k값은 각 데이터들을 불러와서 계산을 해주는 식에 넣어주는 역할을 한다. 
	for(k=0; k<NoOfData; k++) //여기서의 k값은 각 데이터들을 불러와서 계산을 해주는 식에 넣어주는 역할을 한다. 
		{
			sum_m[l] = sum_m[l] + pow(V[k],l);
		}
	}
	

	for(i=0; i<NN; i++) 
	//여기서의 i는 augmented된 옆의 항 즉 n+1렬의 항들의 값들을 구하기 위함이다. 
	{
		for(k=0; k<NoOfData; k++) 
		//마차가지로 k값에대한 for문은 각 데이터들을 수식에 넣어 계산해 주기 위함이다
		{
			sum_r[i] = sum_r[i] + pow(V[k],i)*F[k];		
		} 
		printf("sum_r[%d]= %f\n", i, sum_r[i]); //sum_r[]값 중간 확인
	}
		
	 //여기까지 각 Matrix에 넣을 각 elements들 n, 시그마 x, x^2, x^3, x^4 와 시그마f(x), 시그마 x*f(x) 시그마 x^2*f(x)를 구했다. 이제 각 각 구한 값들을 Matrix에 넣어주도록 한다.
	 
	 for(j=0; j<NN; j++) //j 렬 하나씩 하나씩 고정시키면서 
	{
		for(i=0; i<NN; i++) //i 행을 하나씩 하나씩 바꿔가면서  
		{
			A[i][j]= sum_m[i+j]; 
			//위에서 구한 elements들을 행렬에 집어 넣기 시작한다. n by n 까지  
		}
	}

	
	for(i=0; i<NN; i++)
	{
		A[i][NN] = sum_r[i]; 
		// augmented되어 있는 값을 위해 n+1렬의 값들을 집어 넣어준다  
	}
	

	for(j=0; j<NNp1; j++)
	{
		for(i=0; i<NN; i++)
		{
			printf("to check each elements each A[%d][%d] is = %f \n", i, j, A[i][j]);
		}
	}
	
	//여기까지 하여 Matrix에 위에서 구한 elements들을 모두 집어 넣었다. n by n+1 Matrix 
	//이제 위에서 구한 Matrix를 가지고 Gauss-Jordan Elimination을 통해 a0, a1, a2를 구하자 
	
	//[Guass-Jordan Elimination]

	 for(j=0;j<NN;j++) //J 렬을 고정시키고 
	 {
	 	for(i=0; i<NN; i++) //i 행을 바꿔가면서  
	 	{
	 		if(i!=j)  
			// Diagonal을 제외한 다른 모든 elements들을 0으로 만들어주는 작업을 한다 
	 		{
	 			f=A[i][j]/A[j][j]; //0을 만들어줄 factor를 계산해 줌 
	 			
	 			for(k=0; k<NNp1; k++)
	 			{
	 				A[i][k]= A[i][k]-f*A[j][k]; 
				//Diagonal제외한 다른 elements들을 0으로 만들어주는 작업. 
				 }
			 }
		 }
	 }
	
	
	for(i=0; i<NN; i++)
	{
		a[i] = A[i][NN]/A[i][i]; //Augmented된 맨 우항을 Gauss Jordan Elimination으로 
		                     //제거된 각 Diagonal값으로 나눠줌  --> 해가 된다. 
		                          
	         A[i][i] = A[i][i]/A[i][i]; //각 Diagonal을 1로 만들어줌 
	} 
	
	printf("\n\n", a[i]);  /// 줄바꾸기하여 보기 좋게하기 위함.
	for(i=0; i<NN; i++)
	{
		printf("a=%f \n", a[i]);
	} 
	//여기까지 해서 a1, a2, a3를 다 구했다. 
	
	// [적분구하기]

	//위에서 함수의 원형 선언 했던 것 사용 “사다리꼴 법”, “심슨 법”
	double Sum_Trep = Trep();
	printf("\n\n사다리꼴 방법의 값 (Sum_Trep) = %10.3f", Sum_Trep);
		
	double Sum_Simp= Simp();
	printf("\n\n심슨 방법의 값 (Sum_Simp) = %10.3f", Sum_Simp);
	

	return 0;
}

//[사다리꼴 법]
double Trep()
{
	double area_pre;
	double area_integ;

	int i;
 	double x, fx[ NoOfInterval + 1 ];
 	
 	
 	for(i=0; i < (NoOfInterval + 1); i++)
 	{
 		x = Xstart + Xdel*double(i); //구간 내의 모든 데이터 x값들 
		fx[i] = a[0] + a[1]*x + a[2]*x*x + a[3]*x*x*x;
	}
 	
 	area_pre = 0.0;
 	for(i=1; i < NoOfInterval; i++) //2배 되어있는 부분들 구하는 값
	{
	 	area_pre = area_pre + 2.0*fx[i];
	} 
	area_integ = (Xdel/2.0)*(fx[0] + area_pre + fx[ NoOfInterval ]);
	  
	return area_integ;
}

double Simp()
{
	double area_pre_odd, area_pre_even; 
	double area_integ;
	
	int i;
	double x, fx[NoOfInterval + 1];
	int j;
	
	for(i=0; i< (NoOfInterval+ 1); i++)
	{
		x = Xstart + Xdel*double(i);
		fx[i] = a[0] + a[1]*x + a[2] *x*x + a[3]*x*x*x;
	}
	
	area_pre_odd = 0.0;
	area_pre_even= 0.0;
	
	for(i=1; i<= NoOfInterval/2; i++)
	{
		j = i*2-1;
		area_pre_odd=area_pre_odd+4.0*fx[j];
	}
	
	for(i=1; i<= NoOfInterval/2-1; i++)
	{
		j = i*2;
		area_pre_even = area_pre_even + 2.0*fx[j];
	}
	
	area_integ= (Xdel/3.0)*(fx[0] + fx[NoOfInterval] + area_pre_odd + area_pre_even);
		
	return area_integ;
}
