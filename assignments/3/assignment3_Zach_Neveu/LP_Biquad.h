#ifndef __LP_Biquad_H_INCLUDED__
#define __LP_Biquad_H_INCLUDED__

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * A resonant lowpass filter based on a direct-form 1 biquad implementation
 */
class LP_Biquad {
public:
    LP_Biquad();
    ~LP_Biquad();
    void setup(int SR, float FC, float Q);
    float process(float in);
    void clear();
private:
    float x[3], y[2];
    float a[2], b[3];
};

LP_Biquad::LP_Biquad()
{ 

}
LP_Biquad::~LP_Biquad()
{ 

}

/**
 * Setup coefficients of biquad filter
 */
void LP_Biquad::setup(int SR, float FC, float Q)
{
	float w = 2*(float)M_PI*FC;
	float T = 1.0/SR;
	float denom = (4.0 + 2.0* (w* T)/Q + pow(w, 2)*pow(T, 2));
	b[0] = pow(w, 2)*pow(T, 2) / denom;
	b[1] = 2.0*b[0];
	b[2] = b[0];
	a[0] = (2.*pow(w, 2)*pow(T,2)-8.) / denom;
	a[1] = (4. - 2.*(w/Q)*T+pow(w,2)*pow(T,2)) / denom;
}

/**
 * Process one sample of audio through the biquad and update previous values
 */
float LP_Biquad::process(float in)
{
    x[2] = x[1];
    x[1] = x[0];
    x[0] = in;
    // out = sum(b*x) + sum(a*y)
    float out = b[0]*x[0]+b[1]*x[1]+b[2]*x[2]-a[0]*y[0]-a[1]*y[1];

    y[1] = y[0];
    y[0] = out;
    return out;
}

/**
 * Clear past inputs/outputs of biquad filter
 * Useful  if filter goes unstable for some reason or just to reset it
 */
void LP_Biquad::clear()
{
    x[0] = 0; 
    x[1] = 0; 
    x[2] = 0;
    y[0] = 0;
    y[1] = 0;
}

#endif