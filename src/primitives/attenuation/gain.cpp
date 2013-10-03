#include "gain.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::attenuation::gain::gain(param* v, node* signal) {
    params.push_back(v);

    arity = 1;
    descendants.push_back(signal);

    value = 0.0;

    symbol = "gain";
}

synthax::primitive::attenuation::gain::~gain() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::attenuation::gain* synthax::primitive::attenuation::gain::get_copy() {
    return new gain(params[0]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void synthax::primitive::attenuation::gain::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
	// use unused variables
	firstFrameNumber;
	sampleTimes;
	numConstantVariables;
	constantVariables;

    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] *= value;
    }
}

void synthax::primitive::attenuation::gain::set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    node::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
    // TODO: maybe fill an array with value and use memcpy for terminals? will this be faster?
}

void synthax::primitive::attenuation::gain::done_rendering() {
    node::done_rendering();
    // TODO: free if we do above TODO
}

void synthax::primitive::attenuation::gain::update_mutated_params() {
    node::update_mutated_params();
    value = params[0]->get_value();
    synthax::helpers::intervalMultiply(&minimum, &maximum, params[0]->get_min(), params[0]->get_max(), descendants[0]->minimum, descendants[0]->maximum);
}
