#ifndef SINENODE_H
#define SINENODE_H

#include <math.h>
#include "FunctionNode.h"

class SineNode: public FunctionNode {
public:
    SineNode(GPNode* zero);
    ~SineNode();

	// overrides
    SineNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
	void updateMutatedParams();

private:
};

#endif
