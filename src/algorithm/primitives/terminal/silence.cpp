#include "silence.h"

/*
    ============
    construction
    ============
*/

synthax::node::terminal::silence::silence() {
    arity = 0;

    symbol = "silence";
}

synthax::node::terminal::silence::~silence() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::node::terminal::silence* synthax::node::terminal::silence::get_copy() {
    return new silence();
}

void synthax::node::terminal::silence::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
	// use unused variables
	firstFrameNumber;
	sampleTimes;
	numConstantVariables;
	constantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = 0.0;
    }
}
