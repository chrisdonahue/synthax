#include "CosineNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

CosineNode::CosineNode(node* zero) {
    arity = 1;

    descendants.push_back(zero);

    symbol = "cos";
}

CosineNode::~CosineNode() {
}

/*
    =========
    OVERRidES
    =========
*/

CosineNode* CosineNode::get_copy() {
    CosineNode* ret = new CosineNode(descendants[0] == NULL ? NULL : descendants[0]->get_copy());
    return ret;
}

void CosineNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = cos(buffer[i]);
    }
}

void CosineNode::update_mutated_params() {
    FunctionNode::update_mutated_params();
    minimum = -1.0;
    maximum = 1.0;
}
