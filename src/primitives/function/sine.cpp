#include "sine.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::function::sine::sine(node* zero) {
    arity = 1;

    descendants.push_back(zero);

    symbol = "sin";
	minimum = -1.0f;
	maximum = 1.0f;
	minimum_true = -1.0f;
	maximum_true = 1.0f;
}

synthax::primitive::function::sine::~sine() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::function::sine* synthax::primitive::function::sine::get_copy() {
    sine* ret = new sine(descendants[0] == NULL ? NULL : descendants[0]->get_copy());
    return ret;
}

void synthax::primitive::function::sine::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = sin(buffer[i]);
    }
}

void synthax::primitive::function::sine::update_mutated_params() {
    node::update_mutated_params();
}