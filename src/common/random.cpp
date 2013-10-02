#include "random.h"

synthax::random::random(unsigned s) :
    seed(s), engine(seed), uni_real(0, 1), s(0)
{}

void synthax::random::normalizeDistribution(std::vector<double>* weights) {
    double sum = 0;
    for (std::vector<double>::iterator i = weights->begin(); i != weights->end(); i++) {
        sum += *i;
    }
    for (std::vector<double>::iterator i = weights->begin(); i != weights->end(); i++) {
        *i = (*i) / sum;
    }
}

int synthax::random::sampleFromDistribution(std::vector<double>* weights) {
    // sample from normalized distribution
    double rand = crandom();
    double sum = 0;
    for (unsigned i = 0; i < weights->size(); i++) {
        sum += weights->at(i);
        if (sum > rand)
            return i;
    }
    std::cerr << "Bad distribution sample. This shouldn't happen." << std::endl;
    return -1;
}

double synthax::random::crandom() {
    return uni_real(engine);
}

double synthax::random::gauss() {
    /*
        Copyright Tony Kirke from the Signal Processing Using C++ (SPUC) library
        GNU GPL don't distribute with this code!
    */
    if (s == 0) {
        do {
            v1 = (2.0 * crandom()) - 1.0;
            v2 = (2.0 * crandom()) - 1.0;
            r = (v1*v1) + (v2*v2);
        } while (r >= 1.0);
        fac = sqrt(-2.0 * log(r) / r);
        x = v1 * fac;
        s = 1;
        return (v2*fac);
    }
    else {
        s = 0;
        return x;
    }
}

double synthax::random::whitenoise() {
    return 0.0;
}

// m cannot be returned
int synthax::random::drandom(int m) {
    if (m <= 0) {
        return -1;
    }
    return (int) (crandom() * m);
}