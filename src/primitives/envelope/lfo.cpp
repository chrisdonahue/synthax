#include "lfo.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::envelope::lfo::lfo(param* rate, node* mod)
{
    params.push_back(rate);

    descendants.push_back(mod);
    arity = 1;

    symbol = "lfo*";
}

synthax::primitive::envelope::lfo::~lfo() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::envelope::lfo* synthax::primitive::envelope::lfo::get_copy() {
    return new lfo(params[0]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::envelope::lfo::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        // produce a sine wave at LFO rate
        buffer[i] = buffer[i] * sin(w * (sampleTimes[i]));
    }
}