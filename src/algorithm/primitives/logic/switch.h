#ifndef SWITCHNODE_H
#define SWITCHNODE_H

#include "../../node.h"

class SwitchNode: public node {
public:
    SwitchNode(node* mod, GPNode* sigone, GPNode* sigtwo);
    ~SwitchNode();

	// overrides
    SwitchNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
