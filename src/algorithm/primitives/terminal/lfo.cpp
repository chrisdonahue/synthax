#include "lfo.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::terminal::lfo::lfo(param* rate)
{
    params.push_back(rate);

    arity = 0;
    minimum = -1;
    maximum = 1;
    
    symbol = "lfo";
}

synthax::primitive::terminal::lfo::~lfo() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::terminal::lfo* synthax::primitive::terminal::lfo::get_copy() {
    return new lfo(params[0]->get_copy());
}

void synthax::primitive::terminal::lfo::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    for (unsigned i = 0; i < numSamples; i++) {
        // produce a sine wave at LFO rate
        buffer[i] = sin(w * (sampleTimes[i]));
    }
}