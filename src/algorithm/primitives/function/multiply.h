#ifndef MULTIPLYNODE_H
#define MULTIPLYNODE_H

#include "FunctionNode.h"

class MultiplyNode: public FunctionNode {
public:
    MultiplyNode(node* zero, GPNode* one);
    ~MultiplyNode();

	// overrides
    MultiplyNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
