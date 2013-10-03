#include "wave_table.h"

void synthax::primitive::terminal::wave_table::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
	// use unused variables
	sampleTimes;
	numConstantVariables;
	constantVariables;
	
	// check if first frame number
	if (firstFrameNumber == 0) {
		// reset oscillator
	}
	
	// fill the audio buffer
	float freqVal = (constantVariables[variableNum] * partial) / sampleRate;
    for (unsigned i = 0; i < numSamples; i++) {
        osc->setFrequency(freqVal);
        buffer[i] = osc->getOutput();
        osc->updatePhase(); 
    }
}
