#include "add.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::function::add(node* zero, GPNode* one) {
    arity = 2;

    descendants.push_back(zero);
    descendants.push_back(one);

    symbol = "+";
}

synthax::primitive::function::~add() {
}

/*
    =========
    overrides
    =========
*/

synthax::primitive::function::add* synthax::primitive::function::get_copy() {
    add* ret = new add(descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->get_copy());
    return ret;
}

void synthax::primitive::function::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    descendants[1]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[0]);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = buffer[i] + descendant_buffers[0][i];
    }
}

void synthax::primitive::function::update_mutated_params() {
    node::update_mutated_params();
    synthax::helpers::intervalAdd(&minimum, &maximum, descendants[0]->minimum, descendants[0]->maximum, descendants[1]->minimum, descendants[1]->maximum);
}