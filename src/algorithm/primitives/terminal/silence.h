#ifndef SILENCENODE_H
#define SILENCENODE_H

#include "../../node.h"

class SilenceNode: public node {
public:
    SilenceNode();
    ~SilenceNode();

	// overrides
    SilenceNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

private:
};

#endif
