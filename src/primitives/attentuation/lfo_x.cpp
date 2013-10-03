#include "lfo_x.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::envelope::lfo_x::lfo_x(param* rate, node* mod)
{
    params.push_back(rate);

    descendants.push_back(mod);
    arity = 1;

    symbol = "lfo*";
}

synthax::primitive::envelope::lfo_x::~lfo_x() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::envelope::lfo_x* synthax::primitive::envelope::lfo_x::get_copy() {
    return new lfo_x(params[0]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::envelope::lfo_x::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        // produce a sine wave at lfo_x rate
        buffer[i] = buffer[i] * sin(w * (sampleTimes[i]));
    }
}