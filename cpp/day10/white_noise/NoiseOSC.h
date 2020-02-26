#include <random>

class NoiseOSC {
public:
    NoiseOSC(void);
    ~NoiseOSC();
    float process(void);

protected:
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{0,1};
};

NoiseOSC::NoiseOSC(void) {

}

float NoiseOSC::process(void) {
    return this->d(this->gen);
}

NoiseOSC::~NoiseOSC() {

}