#ifndef SINOSCBASICNODE_H
#define SINOSCBASICNODE_H

#include "../../GPNode.h"

class SinOscBasicNode: public GPNode {
public:
    SinOscBasicNode(GPMutatableParam*, GPMutatableParam*, GPMutatableParam*);
    ~SinOscBasicNode();

	// overrides
    SinOscBasicNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
	void updateMutatedParams();

private:
    int variable_num;
    double partial;
    double phase;
    double w;
};

#endif
