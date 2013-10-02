#include "ConstantNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

ConstantNode::ConstantNode(bool pi, param* v) {
    isPi = pi;
    
    if (!isPi) {
        params.push_back(v);
    }

    arity = 0;

    value = 0.0;

    symbol = "const";
}

ConstantNode::~ConstantNode() {
}

/*
    =========
    OVERRidES
    =========
*/

ConstantNode* ConstantNode::get_copy() {
    return new ConstantNode(isPi, isPi ? NULL : params[0]->get_copy());
}

void ConstantNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
	// use unused variables
	firstFrameNumber;
	sampleTimes;
	numConstantVariables;
	constantVariables;

    // fill buffer with value
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = value;
    }
}

void ConstantNode::set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    node::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
    // TODO: maybe fill an array with value and use memcpy for terminals? will this be faster?
}

void ConstantNode::done_rendering() {
    node::done_rendering();
    // TODO: free if we do above TODO
}

void ConstantNode::update_mutated_params() {
    node::update_mutated_params();
    if (isPi) {
        value = M_PI;
        minimum = M_PI - 1;
        maximum = M_PI + 1;
    }
    else {
        value = params[0]->get_value();
        minimum = params[0]->get_min();
        maximum = params[0]->get_max();
    }
}
