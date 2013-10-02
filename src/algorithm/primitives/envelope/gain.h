#ifndef GAIN_H
#define GAIN_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace envelope{
	class gain : public node {
	public:
		gain(param* v, node* signal);
		~gain();

		// overrides
		gain* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void update_mutated_params();

	private:
		float value;
	};
}}}

#endif
