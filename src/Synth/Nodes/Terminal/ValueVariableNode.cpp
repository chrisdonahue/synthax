#include "ValueVariableNode.h"

/*
    ========================
    CONSTRUCTION/DESTRUCTION
    ========================
*/

ValueVariableNode::ValueVariableNode(GPMutatableParam* vn, GPMutatableParam* range) {
    assert(vn->isUnmutatable());
    variableNum = vn->getDValue();
    mutatableParams.push_back(vn);

    assert(range->isUnmutatable());
    minimum = range->getMin();
    maximum = range->getMax();
    mutatableParams.push_back(range);

    arity = 0;

    symbol = "val_v";
}

ValueVariableNode::~ValueVariableNode() {
}

/*
    =========
    OVERRIDES
    =========
*/

ValueVariableNode* ValueVariableNode::getCopy() {
    return new ValueVariableNode(mutatableParams[0]->getCopy(), mutatableParams[1]->getCopy());
}

void ValueVariableNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) {
    float* variable = variableValues + offset;
    memcpy(buffer, variable, numSamples);
}

void ValueVariableNode::setRenderInfo(float sr, unsigned blockSize, unsigned maxNumFrames, float maxTime) {
    offset = variableNum * blockSize;
}
