#ifndef ADDNODE_H
#define ADDNODE_H

#include "FunctionNode.h"

class AddNode: public FunctionNode {
public:
    AddNode(node* zero, GPNode* one);
    ~AddNode();

	// overrides
    AddNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
