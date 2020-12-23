// The file cordic.h holds definitions for the data types and constant values
#include "ref_cordic.h"

// The cordic_phase array holds the angle for the current rotation
// cordic_phase[0] =~ 0.785
// cordic_phase[1] =~ 0.463
//const static int SIZE = 16;
void cordic(THETA_TYPE theta, COS_SIN_TYPE &sine, COS_SIN_TYPE &cos){
//#pragma HLS INTERFACE ap_ctrl_none port=return
//#pragma HLS INTERFACE s_axilite port=theta
//#pragma HLS INTERFACE s_axilite port=sine
//#pragma HLS INTERFACE s_axilite port=cos

    // Set the initial vector that we will rotate
    // current_cos = I; current_sin = Q
    COS_SIN_TYPE current_cos [12];
    COS_SIN_TYPE current_sin [12];
    COS_SIN_TYPE the [12];
	#pragma HLS array_partition variable=current_cos complete dim=1
	#pragma HLS array_partition variable=current_sin complete dim=1
	#pragma HLS array_partition variable=the complete dim=1
	#pragma HLS array_partition variable=cordic_phase complete dim=1
    // This loop iteratively rotates the initial vector to find the
    // sine and cosine values corresponding to the input theta angle
    current_cos [0] = 0.60735;
    current_sin [0] = 0.0;
    the [0] = theta;
    for (int j = 0; j < NUM_ITERATIONS-1; j++) {
		#pragma HLS dependence variable=current_sin inter false
		#pragma HLS dependence variable=current_cos inter false
		#pragma HLS dependence variable=the inter false
		#pragma HLS pipeline II=1
    	if (the [j] < 0) {
        	current_cos [j+1] = current_cos [j] + (current_sin [j] >> j);
        	current_sin [j+1] = current_sin [j] - (current_cos [j] >> j);
        	the [j+1] = the [j] + cordic_phase[j];
        }
        else {
        	current_cos [j+1] = current_cos [j] - (current_sin [j] >> j);
        	current_sin [j+1] = current_sin [j] + (current_cos [j] >> j);
        	the [j+1] = the [j] - cordic_phase[j];
        }
    }
    
    // Set the final sine and cosine values
	sine= current_sin [11];  cos = current_cos [11];
}

