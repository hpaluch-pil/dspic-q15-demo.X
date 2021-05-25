/*
 * File:   main_q15.c - basics of Q15 number format on dsPIC
 * Please see https://microchipdeveloper.com/dsp0201:numerical-formats
 * for more information
 */

#include "xc.h"
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


int main(void) {
    sum_q15_demo();
    return 0;
}
