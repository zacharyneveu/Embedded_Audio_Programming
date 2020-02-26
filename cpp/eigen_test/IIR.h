#include <Eigen/Dense>

using namespace Eigen;

class IIR
{
public:
    IIR(unsigned int NAS, unsigned int NBS);
    ~IIR(void);
    void setTaps(MatrixXf ataps,MatrixXf btaps);
    float process(float sample);
protected:
    unsigned int NAS, NBS;
    MatrixXf ADL, BDL;
    MatrixXf ATaps, BTaps;
    MatrixXf tmpa, tmpb;
};

IIR::IIR(unsigned int NAS, unsigned int NBS)
{
    this->NAS = NAS;
    this->NBS = NBS;
    this->ADL  = MatrixXf(NAS,1);
    this->BDL  = MatrixXf(NBS,1);
    this->ATaps = MatrixXf(NAS,1);
    this->BTaps = MatrixXf(NBS,1);
    this->tmpa  = MatrixXf(NAS,1);
    this->tmpb  = MatrixXf(NBS,1);

}

void IIR::setTaps(MatrixXf ataps, MatrixXf btaps) {
    this->ATaps = ataps;
    this->BTaps = btaps;
}

float IIR::process(float sample) {
    float outsamp;
    // shift reg b loop
    for (size_t i = 0; i < this->NBS; i++)
    {
        this->BDL(i) = this->BDL(i-1);
    }
    this->BDL(0) = sample;

    // create current output
    this->tmpa = this->BDL.transpose() * this->BTaps;
    this->tmpb = this->ADL.transpose() * this->ATaps;
    outsamp = this->tmpa(0) + this->tmpb(0);

    // shift reg a loop
    for (size_t i = 0; i < this->NAS; i++)
    {
        this->ADL(i) = this->ADL(i-1);
    }
    this->ADL(0) = this->tmpa(0);
    return outsamp;
}

IIR::~IIR() {

}