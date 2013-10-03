#include "sqr_fm.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::modulation::sqr_fm::sqr_fm(param* min_freq, param* max_freq, param* phase, node* freq) {
    params.push_back(min_freq);
    params.push_back(max_freq);
	params.push_back(phase);

    descendants.push_back(freq);
    arity = 1;
    
    minimum = -1.0f;
    maximum = 1.0f;
	minimum_true = -1.0f;
	maximum_true = 1.0f;

    symbol = "sqr_fm";
}

synthax::primitive::modulation::sqr_fm::~sqr_fm() {
}

/*
    ==============
    node overrides
    ==============
*/

synthax::primitive::modulation::sqr_fm* synthax::primitive::modulation::sqr_fm::get_copy() {
    return new sqr_fm(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

/*
    ===================
    wavetable overrides
    ===================
*/

void synthax::primitive::modulation::sqr_fm::defineHarmonics(int len, int numHarmonics, double* ar, double* ai) {
    if (numHarmonics > (len >> 1))
        numHarmonics = (len >> 1);
    
    // clear
    for (int idx = 0; idx < len; idx++) {
        ai[idx] = 0;
        ar[idx] = 0;
    }

	// sqr_fm
	for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
		double temp = idx & 0x01 ? 1.0 / idx : 0.0;
		ar[idx] = -temp;
		ar[jdx] = temp;
	}
}
