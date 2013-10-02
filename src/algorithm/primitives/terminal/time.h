#ifndef TIMENODE_H
#define TIMENODE_H

#include "../../node.h"

class TimeNode: public node {
public:
    TimeNode();
    ~TimeNode();

	// overrides
    TimeNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
	void done_rendering();

private:
};

#endif
