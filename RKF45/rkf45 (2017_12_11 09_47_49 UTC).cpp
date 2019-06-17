#include <iostream>
#include <fstream>
using namespace std;
const double esp = 0.000001;


double cal_f1(double t, double x1, double x2)
{
	return(-9.76 + 0.587*pow((0.25 - x2), 2));
} 

double cal_f0(double t, double x1, double x2)
{
	return(x2);
}

int main(){
	int i, j;
	double t, x[2], h;
	double xT[2];
	double tT;
	double K[6][2];
	double Omg[2];
	double OmgMax;
	double StepRatio;
	int hMinExit = 0;
	ofstream out1;
	out1.open("RK45.txt");
	out1.precision(15);
	if (!out1.is_open()){
		cout << "error open outRK45HW6.text\n";
		cout << "close programs and run again\n";
		cin >> i;
	}
	t = 0;
	x[0] = 100.0;
	x[1] = 0.98;
	h = 0.2;
	StepRatio = 0.01;
	out1 << "t= x1 = x2=\n";
	out1 << t << " " << x[0] << " " << x[1] << " " << "\n";
	for (j = 1; j <= 10000; j++){
		if (t >= 20) break;
		for (i = 1; i <= 100; i++){
			h = h*StepRatio;
			if (h > 0.01) h = 0.2;
			if (h < 0.0000000001){
				h = 0.0000000001;
				hMinExit = 1;
			}
			if (t + h >= 20.0){
				h = 20.0 - t;
			}
			tT = t;
			xT[0] = x[0];
			xT[1] = x[1];
			K[0][0] = cal_f0(tT, xT[0], xT[1]);
			K[0][1] = cal_f1(tT, xT[0], xT[1]);
			tT = t + h / 4.0;
			xT[0] = x[0] + h / 4.0*K[0][0];
			xT[1] = x[1] + h / 4.0*K[0][1];
			K[1][0] = cal_f0(tT, xT[0], xT[1]);
			K[1][1] = cal_f1(tT, xT[0], xT[1]);
			tT = t + h*3.0 / 8.0;
			xT[0] = x[0] + h*(3.0 / 32.0*K[0][0] + 9.0 / 32.0*K[1][0]);
			xT[1] = x[1] + h*(3.0 / 32.0*K[0][1] + 9.0 / 32.0*K[1][1]);
			K[2][0] = cal_f0(tT, xT[0], xT[1]);
			K[2][1] = cal_f1(tT, xT[0], xT[1]);
			tT = t + h*12.0 / 13.0;
			xT[0] = x[0] + h / 2197.0*(1932.0*K[0][0] - 7200.0*K[1][0] + 7296.0*K[2][0]);
			xT[1] = x[1] + h / 2197.0*(1932.0*K[0][1] - 7200.0*K[1][1] + 7296.0*K[2][1]);
			K[3][0] = cal_f0(tT, xT[0], xT[1]);
			K[3][1] = cal_f1(tT, xT[0], xT[1]);
			tT = t + h;
			xT[0] = x[0] + h*(439.0 / 216.0*K[0][0] - 8.0*K[1][0] + 3680.0 / 513.0*K[2][0] - 845.0 / 4104.0*K[3][0]);
			xT[1] = x[1] + h*(439.0 / 216.0*K[0][1] - 8.0*K[1][1] + 3680.0 / 513.0*K[2][1] - 845.0 / 4104.0*K[3][1]);
			K[4][0] = cal_f0(tT, xT[0], xT[1]);
			K[4][1] = cal_f1(tT, xT[0], xT[1]);
			tT = t + h / 2.0;
			xT[0] = x[0] + h*(-8.0 / 27.0*K[0][0] + 2.0*K[1][0] - 3544.0 / 2565.0*K[2][0] + 1859.0 / 4104.0*K[3][0] - 11.0 / 40.0*K[4][0]);
			xT[1] = x[1] + h*(-8.0 / 27.0*K[0][1] + 2.0*K[1][1] - 3544.0 / 2565.0*K[2][1] + 1859.0 / 4104.0*K[3][1] - 11.0 / 40.0*K[4][1]);
			K[5][0] = cal_f0(tT, xT[0], xT[1]);
			K[5][1] = cal_f1(tT, xT[0], xT[1]);
			Omg[0] = h*(K[0][0] / 360.0 - 128.0 / 4275.0*K[2][0] - 2197.0 / 75240.0*K[3][0] + K[4][0] / 50.0 + 2.0 / 55.0*K[5][0]);
			Omg[1] = h*(K[0][1] / 360.0 - 128.0 / 4275.0*K[2][1] - 2197.0 / 75240.0*K[3][1] + K[4][1] / 50.0 + 2.0 / 55.0*K[5][1]);
			if (abs(Omg[0]) > abs(Omg[1])){
				OmgMax = Omg[0];
			}
			else{
				OmgMax = Omg[1];
			}
			if (OmgMax != 0.0){
				StepRatio = pow((abs(esp*h / 2.0 / OmgMax)), 0.25);
			}
			else{
				StepRatio = 1.25;
			}
			if (StepRatio >= 1) break;
			if (hMinExit == 1 && StepRatio < 1){
				cout << "error, reduse h_min or increase epsilon\n";
				cin >> i;
			}
		}
		x[0] = x[0] + h*(16.0 / 135.0*K[0][0] + 6656.0 / 12825.0*K[2][0] + 28561.0 / 56430.0*K[3][0] - 9.0 / 50.0*K[4][0] + 2.0 / 55.0*K[5][0]);
		x[1] = x[1] + h*(16.0 / 135.0*K[0][1] + 6656.0 / 12825.0*K[2][1] + 28561.0 / 56430.0*K[3][1] - 9.0 / 50.0*K[4][1] + 2.0 / 55.0*K[5][1]);

		t = t + h;	
		out1 << " t " << t << " x1 " << x[0] << " x2 " << x[1] << "\n";
	}
	out1.close();
}