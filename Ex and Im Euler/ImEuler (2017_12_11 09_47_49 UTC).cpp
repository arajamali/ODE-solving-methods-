#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double cal_f1(double t,double x1,double x2){ 
	return(-9.7836+0.5874*pow((0.25-x2),2));
}
double cal_f0(double t,double x1, double x2) {
	return(x2);
}

double  ff(double yN);
double  f(double yN1);
double x[2],h,m,t=0;
double eps=pow(10,-10);
double yN,yN1;
int main () {
	int i,j;
	double m,m2, answer;
	
	ofstream x1;
	x1.open("ImEuler.txt");
	x1.precision(15);
	x[0]=100.0;
	x[1]=1.955;
	h=0.2;
	yN=x[0];
	yN1=x[1];
	x1<<"x1= x2=\n";
	x1<<x[0]<<" "<<x[1]<<"\n";
		for(i=1;i<=100;i++){
		for(j=1;j<=100;j++){
			m=(ff(yN+eps)-ff(yN))/eps;
			yN=yN-ff(yN)/m;
			m2=(f(yN1+eps)-f(yN1))/eps;
			yN1=yN1-f(yN1)/m2;
			if (abs(f(yN1))<eps) break;
		}
		t=t+h;
	    x[0]=yN;
		x[1]=yN1;
		x1<<x[0]<<" "<<x[1]<<"\n";
	}

	x1.close();
	return(0);

}
double ff(double yN){
	return(yN-(x[0]+h*cal_f0(t+h,yN,yN1)));
}
double f(double yN1){
	return(yN1-(x[1]+h*cal_f1(t+h,yN,yN1)));
}
