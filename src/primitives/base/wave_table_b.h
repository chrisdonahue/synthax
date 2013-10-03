#ifndef WAVE_TABLE_B_H
#define WAVE_TABLE_B_H

#include "../../node.h"

#include "../../dependencies/WaveTableOsc/WaveTableOsc.h"

namespace synthax{namespace primitive{namespace base{
	class wave_table_b : public node {
	public:
		// construction
		~wave_table_b();

		// overrides
		void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void update_mutated_params();

		// WaveTable helpers
		void fft(int N, double* ar, double* ai);
		float makeAddWaveTable(int len, double* ar, double* ai, double scale, double topFreq);
		void makeAddAllWaveTables(double sampleRate, unsigned overSamp, unsigned constantRatioLimit, double baseFreq, double topFreq);

		// node subclass overrides
		virtual wave_table_b* get_copy() = 0;

		// WaveTable subclass overrides
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
