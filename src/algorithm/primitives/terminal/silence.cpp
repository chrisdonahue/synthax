#include "SilenceNode.h"

/*
    ========================
    construction/DESTRUCTION
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
    OVERRidES
    =========
*/

SilenceNode* SilenceNode::get_copy() {
    return new SilenceNode();
}

void SilenceNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
	// use unused variables
	firstFrameNumber;
	sampleTimes;
	numConstantVariables;
	constantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = 0.0;
    }
}
