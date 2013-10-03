#ifndef WAVE_TABLE_FM_H
#define WAVE_TABLE_FM_H

#include "../base/wave_table_b.h"

namespace synthax{namespace primitive{namespace modulation{
	class wave_table_fm : public synthax::primitive::base::wave_table_b {
	public:
		// node subclass overrides
		void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// node subclass required overrides
		virtual wave_table_fm* get_copy() = 0;
		void update_mutated_params();

		// WaveTable subclass overrides
		virtual void defineHarmonics(int len, int numHarmonics, double* ar, double* ai) = 0;

	private:
		float freq_nyquist;
		float freq_m;
		float freq_b;
	};
}}}

#endif
