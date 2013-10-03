#include "sqr_s_gen.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::terminal::sqr_s_gen::sqr_s_gen(param* vn, param* partial, param* phase) {
    assert(vn->is_unmutatable() && vn->is_discrete());
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(partial);
    params.push_back(phase);

    arity = 0;
    
    minimum = -1.0f;
    maximum = 1.0f;
	minimum_true = -1.0f;
	maximum_true = 1.0f;

    symbol = "sqr_s_gen";
}

synthax::primitive::terminal::sqr_s_gen::~sqr_s_gen() {
}

/*
    ==============
    node overrides
    ==============
*/

synthax::primitive::terminal::sqr_s_gen* synthax::primitive::terminal::sqr_s_gen::get_copy() {
    return new sqr_s_gen(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy());
}

/*
    ===================
    wavetable overrides
    ===================
*/

void synthax::primitive::terminal::sqr_s_gen::defineHarmonics(int len, int numHarmonics, double* ar, double* ai) {
    if (numHarmonics > (len >> 1))
        numHarmonics = (len >> 1);
    
    // clear
    for (int idx = 0; idx < len; idx++) {
        ai[idx] = 0;
        ar[idx] = 0;
    }

	// sqr_s_gen
	for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
		double temp = idx & 0x01 ? 1.0 / idx : 0.0;
		ar[idx] = -temp;
		ar[jdx] = temp;
	}
}