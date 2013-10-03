#include "adsr_x.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::attenuation::adsr_x::adsr_x(param* del, param* atk, param* atkh, param* dec, param* sus, param* sush, param* rel, node* signal)
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

    arity = 1;
    descendants.push_back(signal);

    symbol = "adsr*";
}

synthax::primitive::attenuation::adsr_x::~adsr_x() {
    if (prepared_to_render) {
        free(envelope);
    }
}

/*
    =========
    overrides
    =========
*/

synthax::primitive::attenuation::adsr_x* synthax::primitive::envelope::adsr_x::get_copy() {
    return new adsr_x(params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), params[3]->get_copy(), params[4]->get_copy(), params[5]->get_copy(), params[6]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::attenuation::adsr_x::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    // if frame number is within the envelope
    if (firstFrameNumber < framesInEnvelope)
        releaseFinished = false;
    else
        releaseFinished = true;

    if (!releaseFinished) {
        // TODO: slight enhancement would be to only evaluate remaining samples
        descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
        // if adsr_x hasn't finished releasing but will within these n frames
        if (firstFrameNumber + numSamples > framesInEnvelope) {
            for (unsigned i = 0; firstFrameNumber + i < framesInEnvelope; i++) {
                buffer[i] = buffer[i] * envelope[firstFrameNumber + i];
            }
            for (unsigned i = framesInEnvelope - firstFrameNumber; i < numSamples; i++) {
                buffer[i] = 0.0;
            }
            releaseFinished = true;
        }
        // else if adsr_x hasn't finished releasing and won't within n
        else {
            for (unsigned i = 0; i < numSamples; i++) {
                buffer[i] = buffer[i] * envelope[firstFrameNumber + i];
            }
        }
    }
    else {
        for (unsigned i = 0; i < numSamples; i++) {
            buffer[i] = 0.0;
        }
    }
}