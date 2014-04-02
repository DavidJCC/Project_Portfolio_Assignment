#include "Ackley.h"

Ackley::Ackley(){
}

//
//  Function that calculates Ackley's function, for 2 variables, for specified x & y values
//
double Ackley::ack2Vars(double x, double y){
	double c1=20, c2=0.2, c3=2*PI;

	return -c1*exp(-c2*sqrt(0.5*(x*x + y*y))) - exp(0.5*(cos(c3*x)+cos(c3*y))) + c1 + 1;
}

//
// For a given range of x & y values this function returns the max & min Ackley values found
//
void Ackley::findMinMaxAckley(double sx, double sy, double ex, double ey, double step, double *max, double *min){
	double x, y;
	x = sx;
	*max = -99999.0; *min = 99999.0;
	while(x < ex+step){
		y = sy;
		while(y < ey+step){
			if(ack2Vars(x, y) > *max) *max = ack2Vars(x, y);
			if(ack2Vars(x, y) < *min) *min = ack2Vars(x, y);
			y += step;
		}
		x += step;
	}
}