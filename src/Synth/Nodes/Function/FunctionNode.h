#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "../../GPNode.h"

class FunctionNode: public GPNode {
public:
    // subclass overrides
    virtual FunctionNode* getCopy() = 0;
	virtual void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) = 0;
};

#endif
