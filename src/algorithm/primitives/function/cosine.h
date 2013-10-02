#ifndef COSINENODE_H
#define COSINENODE_H

#include <math.h>
#include "FunctionNode.h"

class CosineNode: public FunctionNode {
public:
    CosineNode(node* zero);
    ~CosineNode();

	// overrides
    CosineNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
