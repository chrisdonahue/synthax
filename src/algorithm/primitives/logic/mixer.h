#ifndef MIXERNODE_H
#define MIXERNODE_H

#include "../../node.h"

class MixerNode: public node {
public:
    MixerNode(node* mod, GPNode* sigone, GPNode* sigtwo);
    ~MixerNode();

	// overrides
    MixerNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
	float controlMin;
	float controlMax;
};

#endif
