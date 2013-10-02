#include "silence.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::terminal::silence::silence() {
    arity = 0;

    symbol = "silence";
}

synthax::primitive::terminal::silence::~silence() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::terminal::silence* synthax::primitive::terminal::silence::get_copy() {
    return new silence();
}

void synthax::primitive::terminal::silence::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
	// use unused variables
	firstFrameNumber;
	sampleTimes;
	numConstantVariables;
	constantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = 0.0;
    }
}
