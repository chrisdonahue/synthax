#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "../../node.h"

class VariableNode: public node {
public:
    VariableNode(param* vn, GPMutatableParam* range);
    ~VariableNode();

	// overrides
    VariableNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

private:
    int variableNum;
};

#endif
