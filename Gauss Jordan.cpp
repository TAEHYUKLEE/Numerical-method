#include <stdio.h>

//Gaus Jordan Elminination 6.14 (a)

double X[3] ;
double A[3][4] = {{3.0, -2.0, 7.0, 15.0}, {-2.0,4.0,-3.0, 12.0}, {-1.0, 9.0, 4.0, 27.0}};


int main(void)
{
	int i,j,k,n;
	double f;  //factor�� f�� 
	n=2;
	
	for(j=0; j<=n;j++) //J Coulum ���� �� Į���� �������鼭 0���� �����. 
	{
		for(i=0;i<=n;i++) //���� j���� ���� ������Ű�� i���� �ٲ㰡�鼭 �������鼭 0���� �����.
		{
			if(i!=j) //Diagonal���� ��� element���� 0���� ����� ���� ���ǹ� 
			{
			     f = A[i][j]/A[j][j]; //Diagonal�� �������� Factor�� ����� 0���� ������ ���� 
			
			for(k=0;k<=n+1;k++)  //i, j�� �����Ǿ� �����Ƿ� ��ü Row operation�� ������ �ʿ��� �װ� k�� (
			{                    //k�� ���� �Űܴٴϸ鼭 Row operation�� ���ش�. 
				
				A[i][k]=A[i][k]-A[j][k]*f; //A[j][j]*c��� ó���� ǥ����  -->  ó���� Diagonal�� �����ؼ� ������, ���⼭�� ��� ���� ���� ��갪�̹Ƿ� [j][k]�� �´�. 
			 } 
	        } 
	    }
	}
	//������� Gaus Jordan Elmination���� Upper Lower Triangle part�� ��� 0���� ������� (Row Operation�� ����) 
	//���� Diagonal�� ��� 1�� ������༭ x1, x2, x3�� ã�ƾ� �Ѵ�. 
	
	for(i=0; i<=2; i++)
	{
		
	X[i] = A[i][n+1]/A[i][i]; // Augmented �� �� ������ ����� 
	 
	A[i][i] = A[i][i]/A[i][i]; //�� Diagonal element���� 1�� ������� 
	}  
	
	for(i=0; i<=2; i++)
	{
		printf("x=%f", X[i]);
	}
	
    
	return 0;
}
