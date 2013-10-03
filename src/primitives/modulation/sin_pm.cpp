#include "sin_pm.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::modulation::sin_pm::sin_pm(param* vn, param* p, param* i, node* mod) {
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

synthax::primitive::modulation::sin_pm::~sin_pm() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::modulation::sin_pm* synthax::primitive::modulation::sin_pm::get_copy() {
    return new sin_pm(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::modulation::sin_pm::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        // equivalent to chowning 1973 FM synthesis assuming buffer is a sine wave
        buffer[i] = sin( (w * (sampleTimes[i]) * (constantVariables[variableNum])) + (index * buffer[i]));
    }
}

void synthax::primitive::modulation::sin_pm::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    w = 2.0 * M_PI * partial;
	
	// update PM params
    index = params[2]->get_cvalue();
    
    // minimum/maximum constant and declared in constructor
}