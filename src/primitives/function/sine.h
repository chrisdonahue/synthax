#ifndef SINENODE_H
#define SINENODE_H

#include <math.h>
#include "FunctionNode.h"

class SineNode: public FunctionNode {
public:
    SineNode(node* zero);
    ~SineNode();

	// overrides
    SineNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
