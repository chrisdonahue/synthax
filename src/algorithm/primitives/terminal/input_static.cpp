#include "VariableNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

VariableNode::VariableNode(param* vn, GPMutatableParam* range) {
    assert(vn->is_unmutatable());
    variableNum = vn->get_dvalue();
    params.push_back(vn);

    assert(range->is_unmutatable());
    minimum = range->get_min();
    maximum = range->get_max();
    params.push_back(range);

    arity = 0;

    symbol = "var";
}

VariableNode::~VariableNode() {
}

/*
    =========
    OVERRidES
    =========
*/

VariableNode* VariableNode::get_copy() {
    return new VariableNode(params[0]->get_copy(), mutatableParams[1]->getCopy());
}

void VariableNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    firstFrameNumber;
    sampleTimes;
    numConstantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = constantVariables[variableNum];
    }
}
