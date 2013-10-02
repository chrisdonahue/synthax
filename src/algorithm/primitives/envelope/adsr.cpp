#include "adsr.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::envelope::adsr::adsr(param* del, GPMutatableParam* atk, GPMutatableParam* atkh, GPMutatableParam* dec, GPMutatableParam* sus, GPMutatableParam* sush, GPMutatableParam* rel, node* signal)
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

synthax::primitive::envelope::adsr::~adsr() {
    if (prepared_to_render) {
        free(envelope);
    }
}

/*
    =========
    overrides
    =========
*/

synthax::primitive::envelope::adsr* synthax::primitive::envelope::adsr::get_copy() {
    return new adsr(params[0]->get_copy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy(), mutatableParams[3]->getCopy(), mutatableParams[4]->getCopy(), mutatableParams[5]->getCopy(), mutatableParams[6]->getCopy(), descendants[0] == NULL ? NULL : descendants[0]->getCopy());
}

void synthax::primitive::envelope::adsr::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    // if frame number is within the envelope
    if (firstFrameNumber < framesInEnvelope)
        releaseFinished = false;
    else
        releaseFinished = true;

    if (!releaseFinished) {
        // TODO: slight enhancement would be to only evaluate remaining samples
        descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
        // if ADSR hasn't finished releasing but will within these n frames
        if (firstFrameNumber + numSamples > framesInEnvelope) {
            for (unsigned i = 0; firstFrameNumber + i < framesInEnvelope; i++) {
                buffer[i] = buffer[i] * envelope[firstFrameNumber + i];
            }
            for (unsigned i = framesInEnvelope - firstFrameNumber; i < numSamples; i++) {
                buffer[i] = 0.0;
            }
            releaseFinished = true;
        }
        // else if ADSR hasn't finished releasing and won't within n
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