#include "sine_phase_mod.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::modulation::sine_phase_mod::sine_phase_mod(param* vn, param* p, param* i, node* mod) {
    assert(vn->is_unmutatable() && vn->is_discrete());
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(p);
    params.push_back(i);

    descendants.push_back(mod);
    arity = 1;
    
    minimum = -1;
    maximum = 1;

    symbol = "sin_pm";
}

synthax::primitive::modulation::sine_phase_mod::~sine_phase_mod() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::modulation::sine_phase_mod* synthax::primitive::modulation::sine_phase_mod::get_copy() {
    return new sine_phase_mod(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::modulation::sine_phase_mod::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        // equivalent to chowning 1973 FM synthesis assuming buffer is a sine wave
        buffer[i] = sin( (w * (sampleTimes[i]) * (constantVariables[variableNum])) + (index * buffer[i]));
    }
}

void synthax::primitive::modulation::sine_phase_mod::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    w = 2.0 * M_PI * partial;
	
	// update PM params
    index = params[2]->get_cvalue();
    
    // minimum/maximum constant and declared in constructor
}