#ifndef SUBTRACTNODE_H
#define SUBTRACTNODE_H

#include "FunctionNode.h"

class SubtractNode: public FunctionNode {
public:
    SubtractNode(node* zero, GPNode* one);
    ~SubtractNode();

	// overrides
    SubtractNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
