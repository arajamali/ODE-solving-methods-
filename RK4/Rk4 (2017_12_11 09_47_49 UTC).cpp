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
int main () {
	int i;
	double t=0,x[2],h;
	double k[4][2];
	ofstream out1;
	out1.open("RK4_2V.txt");
	out1.precision(15);
	if(!out1.is_open()){
		cout<<"error open RK4_2V.txt\n";
		cout<<"close file opened in other program(s) and run again\n";
		cin>>i;
	}
	x[0]=100;
	x[1]=0.9643;
	h=0.2;
	out1<<"x=x1=x2=\n";
	out1<<t<<" "<<x[0]<<" "<<x[1]<<"\n";
	for(i=1;i<=100;i++){
		k[0][0]=cal_f0(t,x[0],x[1]);
		k[0][1]=cal_f1(t,x[0],x[1]);
		k[1][0]=cal_f0(t+0.5*h,x[0]+0.5*h*k[0][0],x[1]+0.5*h*k[0][1]);
		k[1][1]=cal_f1(t+0.5*h,x[0]+0.5*h*k[0][0],x[1]+0.5*h*k[0][1]);
		k[2][0]=cal_f0(t+0.5*h,x[0]+0.5*h*k[1][0],x[1]+0.5*h*k[1][1]);
		k[2][1]=cal_f1(t+0.5*h,x[0]+0.5*h*k[1][0],x[1]+0.5*h*k[1][1]);
		k[3][0]=cal_f0(t+h,x[0]+h*k[2][0],x[1]+h*k[2][1]);
		k[3][1]=cal_f1(t+h,x[0]+h*k[2][0],x[1]+h*k[2][1]);
		x[0]=x[0]+h/6.0*(k[0][0]+2*k[1][0]+2*k[2][0]+k[3][0]);
		x[1]=x[1]+h/6.0*(k[0][1]+2*k[1][1]+2*k[2][1]+k[3][1]);
		t=t+h;
		out1<<t<<" "<<x[0]<<" "<<x[1]<<"\n";
		//out1<<x[0]<<"\n";//<<" "<<x[1]<<"\n";
		
	}
	out1.close();
}

