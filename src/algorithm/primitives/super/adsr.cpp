#include "ADSRTerminalNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

ADSRTerminalNode::ADSRTerminalNode(param* del, GPMutatableParam* atk, GPMutatableParam* atkh, GPMutatableParam* dec, GPMutatableParam* sus, GPMutatableParam* sush, GPMutatableParam* rel)
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

ADSRTerminalNode::~ADSRTerminalNode() {
    if (prepared_to_render) {
        free(envelope);
    }
}

/*
    =========
    OVERRidES
    =========
*/

ADSRTerminalNode* ADSRTerminalNode::get_copy() {
    return new ADSRTerminalNode(params[0]->get_copy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy(), mutatableParams[3]->getCopy(), mutatableParams[4]->getCopy(), mutatableParams[5]->getCopy(), mutatableParams[6]->getCopy());
}

void ADSRTerminalNode::set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    done_rendering();
    sampleRate = sr;
    node::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
}

void ADSRTerminalNode::done_rendering() {
    if (prepared_to_render) {
        sampleRate = 0;
        free(envelope);
    }
    node::done_rendering();
}

void ADSRTerminalNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
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

void ADSRTerminalNode::update_mutated_params() {
    node::update_mutated_params();

	// get minimum value for attack or sustain
    float minAttackHeight = params[2]->get_cmin();
    if (params[5]->get_cmin() < minAttackHeight)
    	minAttackHeight = params[5]->get_cmin();
    
    // get maximum value for attack or sustain
    float maxAttackHeight = params[2]->get_cmax();
    if (params[5]->get_cmax() > maxAttackHeight)
    	maxAttackHeight = params[5]->get_cmax();
    
    // update min/max
    minimum = minAttackHeight;
    maximum = maxAttackHeight;
    
    fillFromParams();
}

/*
    ==============
    CLASS SPECIFIC
    ==============
*/

void ADSRTerminalNode::fillFromParams() {
	// update class values from mutatable params
    delay = params[0]->get_cvalue();
    delayFrames = delay * sampleRate;

    attack = params[1]->get_cvalue();
    attackFrames = delayFrames + attack * sampleRate;
    attackheight = params[2]->get_cvalue();

    decay = params[3]->get_cvalue();
    decayFrames = attackFrames + decay * sampleRate;

    sustain = params[4]->get_cvalue();
    sustainFrames = decayFrames + sustain * sampleRate;
    sustainheight = params[5]->get_cvalue();

    release = params[6]->get_cvalue();
    releaseFrames = sustainFrames + release * sampleRate;

	// calculate the length of the envelope in frames
    framesInEnvelope = (unsigned) (delay * sampleRate) + (unsigned) (attack * sampleRate) + (unsigned) (decay * sampleRate) + (unsigned) (sustain * sampleRate) + (unsigned) (release * sampleRate);

	// if we are pre-rendering the buffer for efficiency do so here
    envelope = (float*) malloc(sizeof(float) * framesInEnvelope);

    // delay
    unsigned framesFilled = 0;
    for (unsigned i = 0; i < (unsigned) (delay * sampleRate); i++, framesFilled++) {
        envelope[framesFilled] = 0.0;
    }
    // attack
    for (unsigned i = 0; i < (unsigned) (attack * sampleRate); i++, framesFilled++) {
        envelope[framesFilled] = (i / (attack * sampleRate)) * attackheight;
    }
    // decay
    for (unsigned i = 0; i < (unsigned) (decay * sampleRate); i++, framesFilled++) {
        envelope[framesFilled] = attackheight - ((i / (decay * sampleRate)) * (attackheight - sustainheight));
    }
    // sustain
    for (unsigned i = 0; i < (unsigned) (sustain * sampleRate); i++, framesFilled++) {
        envelope[framesFilled] = sustainheight;
    }
    // release
    for (unsigned i = 0; i < (unsigned) (release * sampleRate); i++, framesFilled++) {
        envelope[framesFilled]  = sustainheight - ((i / (release * sampleRate)) * (sustainheight));
    }
}
