#ifndef LFOENVELOPENODE_H
#define LFOENVELOPENODE_H

#include "../../node.h"

class LFOEnvelopeNode: public node {
public:
    LFOEnvelopeNode(param* rate, node* mod);
    ~LFOEnvelopeNode();

	// overrides
    LFOEnvelopeNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
    float rate;
    float w;
};

#endif
