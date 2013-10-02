#include "lfo.h"

/*
    ============
    construction
    ============
*/

synthax::node::terminal::lfo::lfo(param* rate)
{
    params.push_back(rate);

    arity = 0;
    minimum = -1;
    maximum = 1;
    
    symbol = "lfo";
}

synthax::node::terminal::lfo::~lfo() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::node::terminal::lfo* synthax::node::terminal::lfo::get_copy() {
    return new lfo(params[0]->get_copy());
}

void synthax::node::terminal::lfo::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    for (unsigned i = 0; i < numSamples; i++) {
        // produce a sine wave at LFO rate
        buffer[i] = sin(w * (sampleTimes[i]));
    }
}