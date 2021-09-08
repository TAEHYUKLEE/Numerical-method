#include <stdio.h>
#include <math.h>

#define  NN    4  // 2���׽��̹Ƿ� ����� 3�� �̹Ƿ� 3X4����� GAUSS JORDAN ����� �ʿ�  : ���� ����
#define  NNp1  5  // 2���׽��̹Ƿ� ����� 3�� �̹Ƿ� 3X4����� GAUSS JORDAN ����� �ʿ�  : ���� ����
#define  NoOfData   12  // �������� ����  
#define  NoOfInterval  100  // ������ ���� ������ ������ ����

// ������ �׷��� ��� 3���Լ��� �׸��� �ִ�. ���� 3���Լ��� �׷������ڴ�. 
// row (��)�� ���� 3��, �� ������ ���� 10�� �̴�. 

double V[NoOfData] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};
double F[NoOfData] = {93, 87, 68, 55, 42, 37, 35, 39, 48, 53, 51, 39};

// 2�� �������̸� (NN=3)   x�� 4�� ���� ��� �׷��Ƿ� ������ʹ� 5�� ������ ( 2*(NN-1) + 1 ) 
//: ���, 1��, 2��, 3��, 4��
// 3�� �������̸� (NN=4)   x�� 6�� ���� ��� �׷��Ƿ� ������ʹ� 7�� ������ ( 2*(NN-1) + 1 ) 
//: ���, 1��, 2��, 3��, 4��, 5��, 6��  
// 4�� �������̸� (NN=5)   x�� 8�� ���� ��� �׷��Ƿ� ������ʹ� 9�� ������ ( 2*(NN-1) + 1 ) 
//: ���, 1��, 2��, 3��, 4��, 5��, 6��, 7��, 8��   

double sum_m[ 2*(NN-1) + 1 ] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

double sum_r[NN]={0.0, 0.0, 0.0, 0.0};

double a[NN];

double A[NN][NNp1];

double Xstart       = 0.0;    // ���б��� ������
double Xstop        =1.1;    // ���б��� ������ ��
double Xdel         = (Xstop - Xstart) / NoOfInterval; // �� ���б����� X��


//// �Ű������� ��ķ� �Ǿ� �ִµ� �������� �ʰ� ����ϸ� ���� �߻��� ==> ������ double a[3]; �� ���ǵ� ������(��, �Ʒ���) �̵�  //************* ����
// �Լ��� ����  // ����� ���������� �ۼ��Ͽ����Ƿ� �Ű������� �Ѱ��� �ʿ� ����
double Trep ();   // ���б����� ���������� �����Ͽ����Ƿ� �Ѱ��� �ʿ� ����.
double Simp ();     

//[Curve fit �ϰ� Matrix���� �����ϴ� ��] 
int main(void)
{
	int l, j, k, i, n, m;
	double f;
	double sum_Trep, sum_simp;

	// 2�� �������̸� (NN=3)   x�� 4��  ( 2*(NN-1) ) ���� ��� 
	// 3�� �������̸� (NN=4)   x�� 6��  ( 2*(NN-1) ) ���� ��� 
	// 4�� �������̸� (NN=5)   x�� 8��  ( 2*(NN-1) ) ���� ��� 
for(l=0; l<=2*(NN-1); l++) // n, x, x^2, x^3, x^4 ���� �ñ׸� ������ ���ϱ� ���� for�� (�������) 
	                 // ���⼭ l ���� �޼��� ��Ÿ����. 
	{
///for(k=0; k<=9; k++) //���⼭�� k���� �� �����͵��� �ҷ��ͼ� ����� ���ִ� �Ŀ� �־��ִ� ������ �Ѵ�. 
	for(k=0; k<NoOfData; k++) //���⼭�� k���� �� �����͵��� �ҷ��ͼ� ����� ���ִ� �Ŀ� �־��ִ� ������ �Ѵ�. 
		{
			sum_m[l] = sum_m[l] + pow(V[k],l);
		}
	}
	

	for(i=0; i<NN; i++) 
	//���⼭�� i�� augmented�� ���� �� �� n+1���� �׵��� ������ ���ϱ� �����̴�. 
	{
		for(k=0; k<NoOfData; k++) 
		//���������� k�������� for���� �� �����͵��� ���Ŀ� �־� ����� �ֱ� �����̴�
		{
			sum_r[i] = sum_r[i] + pow(V[k],i)*F[k];		
		} 
		printf("sum_r[%d]= %f\n", i, sum_r[i]); //sum_r[]�� �߰� Ȯ��
	}
		
	 //������� �� Matrix�� ���� �� elements�� n, �ñ׸� x, x^2, x^3, x^4 �� �ñ׸�f(x), �ñ׸� x*f(x) �ñ׸� x^2*f(x)�� ���ߴ�. ���� �� �� ���� ������ Matrix�� �־��ֵ��� �Ѵ�.
	 
	 for(j=0; j<NN; j++) //j �� �ϳ��� �ϳ��� ������Ű�鼭 
	{
		for(i=0; i<NN; i++) //i ���� �ϳ��� �ϳ��� �ٲ㰡�鼭  
		{
			A[i][j]= sum_m[i+j]; 
			//������ ���� elements���� ��Ŀ� ���� �ֱ� �����Ѵ�. n by n ����  
		}
	}

	
	for(i=0; i<NN; i++)
	{
		A[i][NN] = sum_r[i]; 
		// augmented�Ǿ� �ִ� ���� ���� n+1���� ������ ���� �־��ش�  
	}
	

	for(j=0; j<NNp1; j++)
	{
		for(i=0; i<NN; i++)
		{
			printf("to check each elements each A[%d][%d] is = %f \n", i, j, A[i][j]);
		}
	}
	
	//������� �Ͽ� Matrix�� ������ ���� elements���� ��� ���� �־���. n by n+1 Matrix 
	//���� ������ ���� Matrix�� ������ Gauss-Jordan Elimination�� ���� a0, a1, a2�� ������ 
	
	//[Guass-Jordan Elimination]

	 for(j=0;j<NN;j++) //J ���� ������Ű�� 
	 {
	 	for(i=0; i<NN; i++) //i ���� �ٲ㰡�鼭  
	 	{
	 		if(i!=j)  
			// Diagonal�� ������ �ٸ� ��� elements���� 0���� ������ִ� �۾��� �Ѵ� 
	 		{
	 			f=A[i][j]/A[j][j]; //0�� ������� factor�� ����� �� 
	 			
	 			for(k=0; k<NNp1; k++)
	 			{
	 				A[i][k]= A[i][k]-f*A[j][k]; 
				//Diagonal������ �ٸ� elements���� 0���� ������ִ� �۾�. 
				 }
			 }
		 }
	 }
	
	
	for(i=0; i<NN; i++)
	{
		a[i] = A[i][NN]/A[i][i]; //Augmented�� �� ������ Gauss Jordan Elimination���� 
		                     //���ŵ� �� Diagonal������ ������  --> �ذ� �ȴ�. 
		                          
	         A[i][i] = A[i][i]/A[i][i]; //�� Diagonal�� 1�� ������� 
	} 
	
	printf("\n\n", a[i]);  /// �ٹٲٱ��Ͽ� ���� �����ϱ� ����.
	for(i=0; i<NN; i++)
	{
		printf("a=%f \n", a[i]);
	} 
	//������� �ؼ� a1, a2, a3�� �� ���ߴ�. 
	
	// [���б��ϱ�]

	//������ �Լ��� ���� ���� �ߴ� �� ��� ����ٸ��� ����, ���ɽ� ����
	double Sum_Trep = Trep();
	printf("\n\n��ٸ��� ����� �� (Sum_Trep) = %10.3f", Sum_Trep);
		
	double Sum_Simp= Simp();
	printf("\n\n�ɽ� ����� �� (Sum_Simp) = %10.3f", Sum_Simp);
	

	return 0;
}

//[��ٸ��� ��]
double Trep()
{
	double area_pre;
	double area_integ;

	int i;
 	double x, fx[ NoOfInterval + 1 ];
 	
 	
 	for(i=0; i < (NoOfInterval + 1); i++)
 	{
 		x = Xstart + Xdel*double(i); //���� ���� ��� ������ x���� 
		fx[i] = a[0] + a[1]*x + a[2]*x*x + a[3]*x*x*x;
	}
 	
 	area_pre = 0.0;
 	for(i=1; i < NoOfInterval; i++) //2�� �Ǿ��ִ� �κе� ���ϴ� ��
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
