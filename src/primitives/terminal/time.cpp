#include "time.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::terminal::time::time() {
    arity = 0;

    symbol = "time";
}

synthax::primitive::terminal::time::~time() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::terminal::time* synthax::primitive::terminal::time::get_copy() {
    return new time();
}

void synthax::primitive::terminal::time::set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    maximum = max_frame_start_time;
    node::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
}

void synthax::primitive::terminal::time::done_rendering() {
    if (render_info_set) {
        maximum = 0.0;
    }
	node::done_rendering();
}

void synthax::primitive::terminal::time::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    firstFrameNumber;
    numConstantVariables;
    constantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = sampleTimes[i];
    }
}
