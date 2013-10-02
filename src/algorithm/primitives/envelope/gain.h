#ifndef GAINNODE_H
#define GAINNODE_H

#include "../../node.h"

class GainNode: public node {
public:
    GainNode(param* v, node* signal);
    ~GainNode();

	// overrides
    GainNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
    void done_rendering();
	void update_mutated_params();

private:
    float value;
};

#endif
