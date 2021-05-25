# Learning Q15 fractional numbers on dsPIC

To start utilizing DSP (with its A and B accumulators etc.)
on need to properly understand fractional Q15
(or sometimes referred Q15.1) format.

Please see this page for information on Q15 and dsPIC:
- https://microchipdeveloper.com/dsp0201:numerical-formats


This project is supposed to be run under Simulator only with
suitable breakpoint and Variables window for evaluation.

# Demo functions

* `void sum_q15_demo(void)` - this function sums `0.1 + 0.2` using
   3 different ways (float, Q15(x) conversion, Float2Fract(x) conversion).


Recommended software:
- MPLAB X IDE v5.45
- XC16 v1.70



