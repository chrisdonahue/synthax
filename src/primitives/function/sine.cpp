#include "SineNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

SineNode::SineNode(node* zero) {
    arity = 1;

    descendants.push_back(zero);

    symbol = "sin";
}

SineNode::~SineNode() {
}

/*
    =========
    OVERRidES
    =========
*/

SineNode* SineNode::get_copy() {
    SineNode* ret = new SineNode(descendants[0] == NULL ? NULL : descendants[0]->get_copy());
    return ret;
}

void SineNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = sin(buffer[i]);
    }
}

void SineNode::update_mutated_params() {
    FunctionNode::update_mutated_params();
    minimum = -1.0;
    maximum = 1.0;
}
