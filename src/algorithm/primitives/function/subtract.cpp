#include "SubtractNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

SubtractNode::SubtractNode(node* zero, GPNode* one) {
    arity = 2;

    descendants.push_back(zero);
    descendants.push_back(one);

    symbol = "-";
}

SubtractNode::~SubtractNode() {
}

/*
    =========
    OVERRidES
    =========
*/

SubtractNode* SubtractNode::get_copy() {
    SubtractNode* ret = new SubtractNode(descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->getCopy());
    return ret;
}

void SubtractNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    descendants[1]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[0]);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = buffer[i] - descendant_buffers[0][i];
    }
}

void SubtractNode::update_mutated_params() {
    FunctionNode::update_mutated_params();
    intervalSubtract(&minimum, &maximum, descendants[0]->minimum, descendants[0]->maximum, descendants[1]->minimum, descendants[1]->maximum);
}
