#ifndef SILENCENODE_H
#define SILENCENODE_H

#include "../../GPNode.h"

class SilenceNode: public GPNode {
public:
    SilenceNode();
    ~SilenceNode();

	// overrides
    SilenceNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

private:
};

#endif
