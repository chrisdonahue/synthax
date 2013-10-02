#include "LFOTerminalNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

LFOTerminalNode::LFOTerminalNode(param* rate)
{
    params.push_back(rate);

    arity = 0;
    minimum = -1;
    maximum = 1;
    
    symbol = "lfo";
}

LFOTerminalNode::~LFOTerminalNode() {
}

/*
    =========
    OVERRidES
    =========
*/

LFOTerminalNode* LFOTerminalNode::get_copy() {
    return new LFOTerminalNode(params[0]->get_copy());
}

void LFOTerminalNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    for (unsigned i = 0; i < numSamples; i++) {
        // produce a sine wave at LFO rate
        buffer[i] = sin(w * (sampleTimes[i]));
    }
}

void LFOTerminalNode::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    rate = params[0]->get_value();
    w = 2.0 * M_PI * rate;
	
    // minimum/maximum constant and declared in constructor
}
