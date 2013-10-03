#include "wave_table.h"

/*
    =========
    overrides
    =========
*/

void synthax::primitive::modulation::wave_table::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    // evaluate frequency child
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
	
	// check if first frame number
	if (firstFrameNumber == 0) {
		// reset oscillator
	}
	
	// fill the audio buffer
    float adjusted_child_value;
    float freq_val;
    for (unsigned i = 0; i < numSamples; i++) {
        adjusted_child_value = (buffer[i] * freq_m) + freq_b;
        freq_val = (adjusted_child_value) / sampleRate;
        osc->setFrequency(freq_val);
        buffer[i] = osc->getOutput();
        osc->updatePhase(); 
    }
}

void synthax::primitive::modulation::wave_table::set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
	node::set_render_info(sample_rate, block_size, max_frame_number, max_frame_start_time);
	freq_nyquist = sample_rate / 2;
}

void synthax::primitive::modulation::wave_table::update_mutated_params() {
    node::update_mutated_params();

    // update angular frequency constant
    phase = params[1]->get_value();

    // get min max from descendants
    synthax::helpers::continuous_map_range(descendants[0]->minimum, descendants[0]->maximum, 0.0f, freq_nyquist, &freq_m, &freq_b);
}