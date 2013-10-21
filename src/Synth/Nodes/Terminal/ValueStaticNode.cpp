#include "ValueStaticNode.h"

/*
    ========================
    CONSTRUCTION/DESTRUCTION
    ========================
*/

ValueStaticNode::ValueStaticNode(GPMutatableParam* vn, GPMutatableParam* range) {
    assert(vn->isUnmutatable());
    variableNum = vn->getDValue();
    mutatableParams.push_back(vn);

    assert(range->isUnmutatable());
    minimum = range->getMin();
    maximum = range->getMax();
    mutatableParams.push_back(range);

    arity = 0;

    symbol = "val_s";
}

ValueStaticNode::~ValueStaticNode() {
}

/*
    =========
    OVERRIDES
    =========
*/

ValueStaticNode* ValueStaticNode::getCopy() {
    return new ValueStaticNode(mutatableParams[0]->getCopy(), mutatableParams[1]->getCopy());
}

void ValueStaticNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) {
    float val = constantValues[variableNum];
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = val;
    }
}
