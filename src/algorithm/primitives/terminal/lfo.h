#ifndef LFOTERMINALNODE_H
#define LFOTERMINALNODE_H

#include "../../node.h"

class LFOTerminalNode: public node {
public:
    LFOTerminalNode(param* rate);
    ~LFOTerminalNode();

	// overrides
    LFOTerminalNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
    float rate;
    double w;
};

#endif
