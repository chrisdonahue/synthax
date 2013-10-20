#include "SilenceNode.h"

/*
    ========================
    CONSTRUCTION/DESTRUCTION
    ========================
*/

SilenceNode::SilenceNode() {
    arity = 0;

    symbol = "silence";
}

SilenceNode::~SilenceNode() {
}

/*
    =========
    OVERRIDES
    =========
*/

SilenceNode* SilenceNode::getCopy() {
    return new SilenceNode();
}

void SilenceNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) {
	// use unused variables
	firstFrameNumber;
	sampleTimes;
	constantValues;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = 0.0;
    }
}
