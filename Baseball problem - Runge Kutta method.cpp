////////////////////////////////////// Baseball Tracking ////////////////////////////////////////
#include <stdio.h>
#include <math.h>

double fi = 3.141592653589793238;

double  x[20001], y[20001], z[20001], v[20001], t[20001], vx[20001], vy[20001], vz[20001];

int main(void)
{

	const char* s_output = "Curve.csv";

	FILE* pfo;
		fopen_s(&pfo, s_output, "w");

	double func(double V); //원형 함수 선언

	int n, i;
	double  fx, fx_1, fx_2, fx_3, fsx, fsx_1, fsx_2, fsx_3, t0, tn = 0;
	double  fy, fy_1, fy_2, fy_3, fsy, fsy_1, fsy_2, fsy_3 = 0;
	double  fz, fz_1, fz_2, fz_3, fsz, fsz_1, fsz_2, fsz_3 = 0;
	double  h_X, hh_X, hhh_X, h_Y, hh_Y, hhh_Y, h_Z, hh_Z, hhh_Z;
	double  h_Vx, hh_Vx, hhh_Vx, h_Vy, hh_Vy, hhh_Vy, h_Vz, hh_Vz, hhh_Vz;
	double delt,theta, pi, B, w, g, V, V_h, V_hh, V_hhh;
	theta = (1)*fi / 180;
	pi = (45.0) * fi/180;
	B = 4.1 * pow(10, -4);
	w = 1800;
	g = 9.81;
	t0 = 0;
	tn = 20;
	delt = 0.001;
	n = (tn - t0) / delt;  
							  
	//초기값 설정 
	x[0] = 0.0;
	y[0] = 0.0;
	z[0] = 1.7; //h: 1.7m
	t[0] = 0.0;
	v[0] = 30;
	vx[0], vy[0], vz[0] = 0.0;
	
	for (i = 0; i <= n; i++) {

		t[i] = delt * i;
	}


//////////////////////////////////////////// 4th Order Runge Kutta //////////////////////////////////////////////

	for (i = 0; i < n; i++)
	{

		/////////////////////////////// x- direction ////////////////////////////////
		V= sqrt(pow(vx[i], 2)+ pow(vy[i], 2)+ pow(vz[i], 2));
		
		fx = vx[i];
		fsx = -func(V) * V * vx[i] + B * w * (vz[i] * sin(pi) - vy[i] * cos(pi));
		
		fy = vy[i];
		fsy = -func(V) * V * vy[i] + B * w * (vx[i] * cos(pi));

		fz = vz[i];
		fsz = -g -func(V) * V * vz[i] + B * w * (vx[i] * sin(pi));

		//step1 (Initial Condition으로) (k1의 half step으로 점 찍기)
		h_X = x[i] + delt / (2.0) * fx; //half step x
		h_Vx = v[i] + delt / (2.0) * fsx; //half step vx
		h_Y = x[i] + delt / (2.0) * fy; //half step y
		h_Vy = v[i] + delt / (2.0) * fsy; //half step vy
		h_Z = x[i] + delt / (2.0) * fz; //half step z
		h_Vz = v[i] + delt / (2.0) * fsz; //half step vz

		//중간에 V_h를 구해줘야함
		V_h = sqrt(pow(h_Vx, 2) + pow(h_Vy, 2) + pow(h_Vz, 2));

		fx_1 = (h_X * cos(theta)); // need half step t, x, v(v도 x,y,z: half step)
		fsx_1 = -func(V_h) * V_h * h_Vx + B * w * (h_Vz * sin(pi) - h_Vy * cos(pi)); //for next step

		fy_1 = 0; // need half step t, x, v(v도 x,y,z: half step)
		fsy_1 = -func(V_h) * V_h * h_Vy + B * w * (h_Vx * cos(pi));

		fz_1 = (h_Z * sin(theta)); // need half step t, x, v(v도 x,y,z: half step)
		fsz_1 = -g - func(V_h) * V_h * h_Vz + B * w * (h_Vx * sin(pi));

		//step2 (그다음 k2의 Half step으로 점찍기)
		hh_X = x[i] + delt / (2.0) * fx_1;
		hh_Vx = v[i] + delt / (2.0) * fsx_1;
		hh_Y = x[i] + delt / (2.0) * fy_1; //half step y 
		//x[i]인 이유는 다시 돌아와서 원래의 점에서 Half step이기때문에
		hh_Vy = v[i] + delt / (2.0) * fsy_1; //half step vy
		hh_Z = x[i] + delt / (2.0) * fz_1; //half step z
		hh_Vz = v[i] + delt / (2.0) * fsz_1; //half step vz
		
		//중간에 V_hh를 구해줘야함
		V_hh = sqrt(pow(hh_Vx, 2) + pow(hh_Vy, 2) + pow(hh_Vz, 2));

		fx_2 = (hh_X * cos(theta));
		fsx_2 = -func(V_hh) * V_hh * hh_Vx + B * w * (hh_Vz * sin(pi) - hh_Vy * cos(pi));

		fy_2 = 0;
		fsy_2 = -func(V_hh) * V_hh * hh_Vy + B * w * (hh_Vx * cos(pi));

		fz_2 = (hh_Z * sin(theta));
		fsz_2 = -g - func(V_hh) * V_hh * hh_Vz + B * w * (hh_Vx * sin(pi));
		
		//step3 (K3의 Half step으로 점찍기)
		hhh_X = x[i] + delt / (2.0) * fx_2;
		hhh_Vx = v[i] + delt / (2.0) * fsx_2;
		hhh_Y = x[i] + delt / (2.0) * fy_2; //half step y 
		hhh_Vy = v[i] + delt / (2.0) * fsy_2; //half step vy
		hhh_Z = x[i] + delt / (2.0) * fz_2; //half step z
		hhh_Vz = v[i] + delt / (2.0) * fsz_2; //half step vz

		//중간에 V_hhh를 구해줘야함
		V_hhh = sqrt(pow(hhh_Vx, 2) + pow(hhh_Vy, 2) + pow(hhh_Vz, 2));

		///k4구하기
		fx_3 = (hhh_X * cos(theta));
		fsx_3 = -func(V_hhh) * V_hhh * hhh_Vx + B * w * (hhh_Vz * sin(pi) - hhh_Vy * cos(pi));

		fy_3 = 0;
		fsy_3 = -func(V_hhh) * V_hhh * hhh_Vy + B * w * (hhh_Vx * cos(pi));

		fz_3 = (hhh_Z * sin(theta));
		fsz_3 = -g - func(V_hhh) * V_hhh * hhh_Vz + B * w * (hhh_Vx * sin(pi));

		//각 점 x,y,z에 대해서 위치와 속도 구해보기
		x[i + 1] = x[i] + delt * ((1.0 / 6.0) * fx + (1.0 / 3.0) * fx_1 + (1.0 / 3.0) * fx_2 + (1.0 / 6.0) * fx_3);		   
		vx[i + 1] = vx[i] + delt * ((1.0 / 6.0) * fsx + (1.0 / 3.0) * fsx_1 + (1.0 / 3.0) * fsx_2 + (1.0 / 6.0) * fsx_3);

		y[i + 1] = y[i] + delt * ((1.0 / 6.0) * fy + (1.0 / 3.0) * fy_1 + (1.0 / 3.0) * fy_2 + (1.0 / 6.0) * fy_3);
		vy[i + 1] = vy[i] + delt * ((1.0 / 6.0) * fsy + (1.0 / 3.0) * fsy_1 + (1.0 / 3.0) * fsy_2 + (1.0 / 6.0) * fsy_3);

		z[i + 1] = z[i] + delt * ((1.0 / 6.0) * fz + (1.0 / 3.0) * fz_1 + (1.0 / 3.0) * fz_2 + (1.0 / 6.0) * fz_3);
		vz[i + 1] = vz[i] + delt * ((1.0 / 6.0) * fsz + (1.0 / 3.0) * fsz_1 + (1.0 / 3.0) * fsz_2 + (1.0 / 6.0) * fsz_3);
			   		
	}

	for (i = 0; i < n;i++) {

		fprintf(pfo, "%10.9lf, %10.9lf, %10.9lf\n", x[i], y[i], z[i]);

		printf("x[%d]: %f, vx[%d]: %f\n", i, x[i], i, vx[i]);
		printf("y[%d]: %f, vy[%d]: %f\n", i, y[i], i, vy[i]);
		printf("z[%d]: %f, vz[%d]: %f\n", i, z[i], i, vz[i]);
		
		if (fabs(x[i + 1] - 18.39) < 0.01) {
			break;
		}
	}
fclose(pfo);

return 0;
}

double func(double V) {

	double F;

	F = 0.0039 + 0.0058 / (1 + exp((V - 35) / 5));
	
	return F;

}