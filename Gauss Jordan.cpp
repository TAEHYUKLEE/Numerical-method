#include <stdio.h>

//Gauss Jordan Elminination 6.14 (a)

double X[3] ;
double A[3][4] = {{3.0, -2.0, 7.0, 15.0}, {-2.0,4.0,-3.0, 12.0}, {-1.0, 9.0, 4.0, 27.0}};


int main(void)
{
	int i,j,k,n;
	double f;  //factor의 f로 
	n=2;
	
	for(j=0; j<=n;j++) //J Coulum 고정 한 칼럼씩 내려가면서 0으로 만든다. 
	{
		for(i=0;i<=n;i++) //위의 j에서 렬을 고정시키고 i행을 바꿔가면서 내려가면서 0으로 만든다.
		{
			if(i!=j) //Diagonal외의 모든 element들을 0으로 만들기 위한 조건문 
			{
			     f = A[i][j]/A[j][j]; //Diagonal을 기준으로 Factor를 만들어 0으로 제거해 나감 
			
			for(k=0;k<=n+1;k++)  //i, j는 고정되어 있으므로 전체 Row operation할 변수가 필요함 그게 k임 (
			{                    //k로 렬을 옮겨다니면서 Row operation을 해준다. 
				
				A[i][k]=A[i][k]-A[j][k]*f; //A[j][j]*c라고 처음에 표기함  -->  처음에 Diagonal을 생각해서 했지만, 여기서는 모든 열에 대한 계산값이므로 [j][k]가 맞다. 
			 } 
	        } 
	    }
	}
	//여기까지 Gaus Jordan Elmination으로 Upper Lower Triangle part를 모두 0으로 만들었다 (Row Operation을 통한) 
	//이제 Diagonal을 모두 1로 만들어줘서 x1, x2, x3를 찾아야 한다. 
	
	for(i=0; i<=2; i++)
	{
		
	X[i] = A[i][n+1]/A[i][i]; // Augmented 된 맨 우항을 계산함 
	 
	A[i][i] = A[i][i]/A[i][i]; //각 Diagonal element들을 1로 만들어줌 
	}  
	
	for(i=0; i<=2; i++)
	{
		printf("x=%f", X[i]);
	}
	
    
	return 0;
}
