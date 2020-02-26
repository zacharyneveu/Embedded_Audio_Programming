#include <Eigen/Dense>

using namespace Eigen;

class FIR
{
public:
    FIR(unsigned int NTAPS);
    ~FIR(void);
    void setTaps(MatrixXf taps);
    float process(float sample);
protected:
    unsigned int NTAPS;
    MatrixXf TDL;
    MatrixXf Taps;
    MatrixXf tmp;
};

FIR::FIR(unsigned int NTAPS)
{
    this->NTAPS = NTAPS;
    this->TDL  = MatrixXf(NTAPS,1);
    this->Taps = MatrixXf(NTAPS,1);
    this->tmp  = MatrixXf(NTAPS,1);

}

void FIR::setTaps(MatrixXf taps) {
    this->Taps = taps;
}

float FIR::process(float sample) {
    // shift reg loop
    for (size_t i = 0; i < this->NTAPS; i++)
    {
        this->TDL(i) = this->TDL(i-1);
    }
    this->TDL(0) = sample;
    this->tmp = this->TDL.transpose() * this->Taps;
    return this->tmp(0);
}

FIR::~FIR() {

}