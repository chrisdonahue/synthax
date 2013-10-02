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