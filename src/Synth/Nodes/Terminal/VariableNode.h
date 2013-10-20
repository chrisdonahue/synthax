#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "../../GPNode.h"

class VariableNode: public GPNode {
public:
    VariableNode(GPMutatableParam* vn, GPMutatableParam* range);
    ~VariableNode();

	// overrides
    VariableNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

private:
    int variableNum;
};

#endif
