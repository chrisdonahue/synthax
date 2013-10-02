#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "../../node.h"

class ConstantNode: public node {
public:
    ConstantNode(bool pi, param* v);
    ~ConstantNode();

	// overrides
    ConstantNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
    void done_rendering();
	void update_mutated_params();

private:
    bool isPi;
    double value;
};

#endif
