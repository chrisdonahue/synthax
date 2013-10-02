#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "../../node.h"

class FunctionNode: public node {
public:
    // subclass overrides
    virtual FunctionNode* get_copy() = 0;
	virtual void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) = 0;
};

#endif