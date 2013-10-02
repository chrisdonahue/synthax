#ifndef WAVETABLE_H
#define WAVETABLE_H

#include "../../node.h"
#include "../../../Dependencies/WaveTableOsc/WaveTableOsc.h"

namespace synthax{namespace node{namespace terminal{
	class wave_table : public node {
	public:
		// overrides
		void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);
		void update_mutated_params();

		// WaveTable helpers
		void fft(int N, double* ar, double* ai);
		float makeAddWaveTable(int len, double* ar, double* ai, double scale, double topFreq);

		// node subclass overrides
		virtual wave_table* get_copy() = 0;

		// WaveTable subclass overrides
		virtual void makeAddAllWaveTables(double sampleRate, unsigned overSamp, unsigned constantRatioLimit, double baseFreq, double topFreq) = 0;
		virtual void defineHarmonics(int len, int numHarmonics, double* ar, double* ai) = 0;

		// member variables
		int variableNum;
		float sampleRate;
		float partial;
		float phase;
		WaveTableOsc* osc;
	private:
	};
}}}

#endif
