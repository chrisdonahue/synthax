#include "TimeNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

TimeNode::TimeNode() {
    arity = 0;

    symbol = "time";
}

TimeNode::~TimeNode() {
}

/*
    =========
    OVERRidES
    =========
*/

TimeNode* TimeNode::get_copy() {
    return new TimeNode();
}

void TimeNode::set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    maximum = max_frame_start_time;
    node::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
}

void TimeNode::done_rendering() {
    if (renderInfoSet) {
        maximum = 0.0;
    }
}

void TimeNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    firstFrameNumber;
    numConstantVariables;
    constantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = sampleTimes[i];
    }
}
