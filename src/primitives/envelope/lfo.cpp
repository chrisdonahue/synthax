#include "LFOEnvelopeNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

LFOEnvelopeNode::LFOEnvelopeNode(param* rate, node* mod)
{
    params.push_back(rate);

    descendants.push_back(mod);
    arity = 1;

    symbol = "lfo*";
}

LFOEnvelopeNode::~LFOEnvelopeNode() {
}

/*
    =========
    OVERRidES
    =========
*/

LFOEnvelopeNode* LFOEnvelopeNode::get_copy() {
    return new LFOEnvelopeNode(params[0]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->getCopy());
}

void LFOEnvelopeNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        // produce a sine wave at LFO rate
        buffer[i] = buffer[i] * sin(w * (sampleTimes[i]));
    }
}

void LFOEnvelopeNode::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    rate = params[0]->get_value();
    w = 2.0 * M_PI * rate;
	
    // minimum/maximum calculation
    intervalMultiply(&minimum, &maximum, -1.0f, 1.0f, descendants[0]->minimum, descendants[0]->maximum);
}
