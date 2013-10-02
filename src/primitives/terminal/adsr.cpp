#include "adsr.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::terminal::adsr::adsr(param* del, param* atk, param* atkh, param* dec, param* sus, param* sush, param* rel)
{
    releaseFinished = false;
    framesInEnvelope = 0;
    envelope = NULL;
    sampleRate = 0;

    params.push_back(del);
    params.push_back(atk);
    params.push_back(atkh);
    params.push_back(dec);
    params.push_back(sus);
    params.push_back(sush);
    params.push_back(rel);

    arity = 0;

    symbol = "adsr";
}

synthax::primitive::terminal::adsr::~adsr() {
    if (prepared_to_render) {
        free(envelope);
    }
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::terminal::adsr* synthax::primitive::terminal::adsr::get_copy() {
    return new adsr(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), params[3]->get_copy(), params[4]->get_copy(), params[5]->get_copy(), params[6]->get_copy());
}

void synthax::primitive::terminal::adsr::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    // if frame number is within the envelope
    if (firstFrameNumber < framesInEnvelope)
        releaseFinished = false;
    else
        releaseFinished = true;

    // if this is a terminal node
    if (!releaseFinished) {
        if (firstFrameNumber + numSamples > framesInEnvelope) {
            for (unsigned i = 0; firstFrameNumber + i < framesInEnvelope; i++) {
                buffer[i] = envelope[firstFrameNumber + i];
            }
            for (unsigned i = framesInEnvelope - firstFrameNumber; i < numSamples; i++) {
                buffer[i] = 0.0;
            }
            releaseFinished = true;
        }
        else {
            for (unsigned i = 0; i < numSamples; i++) {
                buffer[i] = envelope[firstFrameNumber + i];
            }
        }
    }
    else {
        for (unsigned i = 0; i < numSamples; i++) {
            buffer[i] = 0.0;
        }
    }
}