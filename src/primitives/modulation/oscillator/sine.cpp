#include "sine.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::modulation::sine::sine(param* min_freq, param* max_freq, param* phase, node* freq) {
    params.push_back(min_freq);
    params.push_back(max_freq);
	params.push_back(phase);

    descendants.push_back(freq);
    arity = 1;
    
    minimum = -1.0f;
    maximum = 1.0f;
	minimum_true = -1.0f;
	maximum_true = 1.0f;

    symbol = "sin_fm";
}

synthax::primitive::modulation::sine::~sine() {
}

/*
    ==============
    node overrides
    ==============
*/

synthax::primitive::modulation::sine* synthax::primitive::modulation::sine::get_copy() {
    return new sine(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

/*
    ===================
    wavetable overrides
    ===================
*/

void synthax::primitive::modulation::sine::defineHarmonics(int len, int numHarmonics, double* ar, double* ai) {
    if (numHarmonics > (len >> 1))
        numHarmonics = (len >> 1);
    
    // clear
    for (int idx = 0; idx < len; idx++) {
        ai[idx] = 0;
        ar[idx] = 0;
    }

    // sin
    ar[1] = 1.0f;
    ar[len - 1] = -1.0f;

    /*
    for (int idx = 0; idx < len; idx++) {
        std::cout << "idx: " << idx << ", ar[idx]: " << ar[idx] << ", ai[idx]: " << ai[idx] << std::endl;
    }
    */
}
