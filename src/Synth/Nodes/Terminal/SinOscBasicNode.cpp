#include "SinOscBasicNode.h"

/*
    ========================
    CONSTRUCTION/DESTRUCTION
    ========================
*/

SinOscBasicNode::SinOscBasicNode(GPMutatableParam* vn, GPMutatableParam* partial, GPMutatableParam* phase) {
    assert(vn->isUnmutatable() && vn->isDiscrete());
    variable_num = vn->getDValue();
    mutatableParams.push_back(vn);
    mutatableParams.push_back(partial);
    mutatableParams.push_back(phase);

    arity = 0;

    minimum = -1.0f;
    maximum = 1.0f;

    symbol = "sinoscb_s";
}

SinOscBasicNode::~SinOscBasicNode() {
}

/*
    =========
    OVERRIDES
    =========
*/

SinOscBasicNode* SinOscBasicNode::getCopy() {
    return new SinOscBasicNode(mutatableParams[0]->getCopy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy());
}

void SinOscBasicNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) {
    // fill buffer with value
    float frequency = constantValues[variable_num];
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = (float) sin(w * frequency * sampleTimes[i] + phase);
    }
}

void SinOscBasicNode::updateMutatedParams() {
    GPNode::updateMutatedParams();
    partial = mutatableParams[1]->getValue();
    phase = mutatableParams[2]->getValue() * 2 * M_PI;
    w = 2 * M_PI * partial;
}
