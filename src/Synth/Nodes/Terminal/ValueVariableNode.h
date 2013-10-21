#ifndef VALUEVARIABLENODE_H
#define VALUEVARIABLENODE_H

#include <string.h>
#include "../../GPNode.h"

class ValueVariableNode: public GPNode {
public:
    ValueVariableNode(GPMutatableParam* vn, GPMutatableParam* range);
    ~ValueVariableNode();

	// overrides
    ValueVariableNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
    void setRenderInfo(float sr, unsigned blockSize, unsigned maxNumFrames, float maxTime);

private:
    int variableNum;
    unsigned offset;
};

#endif
