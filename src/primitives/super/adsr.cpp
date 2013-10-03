#include "adsr.h"

/*
    =========
    OVERRidES
    =========
*/

void synthax::primitive::super::adsr::set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    node::set_render_info(sample_rate, block_size, max_frame_number, max_frame_start_time);
	done_rendering();
    sampleRate = sample_rate;
}

void synthax::primitive::super::adsr::done_rendering() {
    node::done_rendering();
    if (prepared_to_render) {
        sampleRate = 0;
        free(envelope);
    }
}

void synthax::primitive::super::adsr::update_mutated_params() {
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

void synthax::primitive::super::adsr::fillFromParams() {
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
