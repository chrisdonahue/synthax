#ifndef LFOENVELOPENODE_H
#define LFOENVELOPENODE_H

#include "../../GPNode.h"

class LFOEnvelopeNode: public GPNode {
public:
    LFOEnvelopeNode(GPMutatableParam* rate, GPNode* mod);
    ~LFOEnvelopeNode();

	// overrides
    LFOEnvelopeNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
	void updateMutatedParams();

private:
    float rate;
    float w;
};

#endif
