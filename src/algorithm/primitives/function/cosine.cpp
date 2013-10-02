#include "cosine.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::function::cosine::cosine(node* zero) {
    arity = 1;

    descendants.push_back(zero);

    symbol = "cos";
}

synthax::primitive::function::cosine::~cosine() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::function::cosine* synthax::primitive::function::cosine::get_copy() {
    cosine* ret = new cosine(descendants[0] == NULL ? NULL : descendants[0]->get_copy());
    return ret;
}

void synthax::primitive::function::cosine::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = cos(buffer[i]);
    }
}

void synthax::primitive::function::cosine::update_mutated_params() {
    node::update_mutated_params();
    minimum = -1.0;
    maximum = 1.0;
}
