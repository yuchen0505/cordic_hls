#include "ref_cordic.h"
#include <iostream>

int main () {
	int NUM_DEGREE=90;
	THETA_TYPE pi = 3.1415926536897932384626;
	THETA_TYPE theta;
	COS_SIN_TYPE c;
	COS_SIN_TYPE s;
	for (int i = 0; i < NUM_DEGREE; i++){
		theta = i*pi/180;
		cordic (theta, s, c);
		std::cout << "Sine : "   << s << std::endl;
		std::cout << "Cosine : " << c << std::endl;
	}
	return 0;
}
