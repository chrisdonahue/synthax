#ifndef TIME_H
#define TIME_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace terminal{
	class time: public node {
	public:
		time();
		~time();

		// overrides
		time* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();

	private:
	};
}}}

#endif
