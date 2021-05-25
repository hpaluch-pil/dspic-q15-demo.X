/*
 * File:   main_q15.c - basics of Q15 number format on dsPIC
 * Please see https://microchipdeveloper.com/dsp0201:numerical-formats
 * for more information
 */

#include "xc.h"
#include <stdint.h>
#include <dsp.h>

// summing Q15 demo. It sums 0.1 + 0.2 in 3 ways:
// 1. as floats: 0.1 + 0.2
// 2. as Q15 using Q15(0.1)+Q15(0.2)
// 3. as Q15 using Float2Fract(0.1) + Float2Fract(0.2)
// NOTICE that 2. and 3. returns different results (single bit error)
void sum_q15_demo(void)
{
    // we use volatile so variables are always visible and not optimized out
    volatile float f_1 = 0.1;
    volatile float f_2 = 0.2;
    volatile float f_sum;

    // int is used as fractional (int16_t) in dsp.h
    volatile int q_1, q_2, q_sum;
    volatile float f_q_sum;

    // now we use Float2Fract() conversion routrine
    volatile int qq_1, qq_2, qq_sum;
    volatile float f_qq_sum;
          
    f_sum = f_1 + f_2;
    
    q_1 = Q15(f_1); q_2 = Q15(f_2); q_sum = q_1 + q_2;
    f_q_sum = Fract2Float(q_sum);
    
    qq_1 = Float2Fract(f_1); qq_2 = Float2Fract(f_2);
    qq_sum = qq_1 + qq_2;
    f_qq_sum = Fract2Float(qq_sum);
    asm("NOP"); // for breakpoint
}

void mul_q15_m1_m1(void)
{
    int16_t q15_m1 = 0x8000; // -1.0 in Q15.1 format
    int16_t q15_mhalf = 0xc000; // -0.5 in Q15.1
    int32_t r1_tmp;
    int16_t r1,r2;
    float f1,f2;
    
    r1_tmp = (((int32_t)q15_m1)*q15_m1) >> 15;
    r1 = (int16_t)r1_tmp;
    f1 = Fract2Float(r1);

    r2 = (int16_t)((((int32_t)q15_m1)*q15_mhalf) >> 15);
    f2 = Fract2Float(r2);
    asm("NOP");
}



#define N_X1_S 5
float x1_s[N_X1_S] = {
  -1.0,-0.5,0.0,0.5,9.999969
};
float x2 = 0.123;


// simple q15 multiplication demo
void mul_q15_demo(void)
{
    float x1_s_times_x2[N_X1_S];
    int16_t q15_x1_s[N_X1_S];
    int16_t q15_x2;
    int16_t q15_res_s[N_X1_S];
    float q15_final[N_X1_S];
    int i;
    
    q15_x2 = Float2Fract(x2);
    
    for(i=0;i<N_X1_S;i++){
        // computation in float for verification
        x1_s_times_x2[i] = x1_s[i] * x2;
        // convert x1_s to Q15
        q15_x1_s[i] = Float2Fract(x1_s[i]);
        // multiply and rotate Q30 to Q15
        q15_res_s[i] = (int16_t)(((int32_t)q15_x2) * q15_x1_s[i] >> 15);
        q15_final[i] = Fract2Float(q15_res_s[i]);
    }
    asm("NOP");
}


// values for square from 0.0 to 9.99969)
// we can't use 10.0 safely because Q15 allows only -1.0 to +9.99969
#define N_X_VALS 7
float x_vals[N_X_VALS] = {
    0.0, 0.5, 5.0, 9.9, 9.999969, -0.5, -1.0
};

// ratio to normalize max x 9.999969 into Q15 
#define X_Q15_RATIO 10

void square_q15_demo(void)
{
    float x_squared[N_X_VALS];
    int x_q15[N_X_VALS]; // normalized X values in Q15 format
    int32_t q15_squared[N_X_VALS]; //notice that we must use int32_t for square!!!
    int q15_sq2[N_X_VALS];
    float q15_results[N_X_VALS];
    int i;
    
    for(i=0;i<N_X_VALS;i++){
        // initialize x_15 - normalized Q15
        x_q15[i] = Q15( x_vals[i] / X_Q15_RATIO );

        // use standard float * float square for verification
        x_squared[i] = x_vals[i] * x_vals[i];

        // now square Q15 value - expands from Q15 to Q31
        q15_squared[i]= ((int32_t)x_q15[i]) * x_q15[i];
        q15_sq2[i] = (int16_t)(q15_squared[i] / 32768);
        q15_results[i] = Fract2Float(q15_sq2[i])
                * X_Q15_RATIO * X_Q15_RATIO;
    }
    asm("NOP"); // put breakpoint here
}

int main(void) {
    mul_q15_m1_m1();
    // mul_q15_demo();
    //    sum_q15_demo();
    //square_q15_demo();
    return 0;
}
