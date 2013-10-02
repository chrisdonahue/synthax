#ifndef TERMINAL_WAVE_TABLE_H
#define TERMINAL_WAVE_TABLE_H

#include "../super/wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class wave_table : public synthax::primitive::super::wave_table {
	public:
		// overrides
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// node subclass overrides
		virtual wave_table* get_copy() = 0;

		// WaveTable subclass overrides
		virtual void defineHarmonics(int len, int numHarmonics, double* ar, double* ai) = 0;
	private:
	};
}}}

#endif
