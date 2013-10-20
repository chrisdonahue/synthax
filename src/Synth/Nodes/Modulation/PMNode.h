#ifndef PMNODE_H
#define PMNODE_H

#include "../../GPNode.h"

class PMNode: public GPNode {
public:
    PMNode(GPMutatableParam* vn, GPMutatableParam* p, GPMutatableParam* i, GPNode* mod);
    ~PMNode();

	// overrides
    PMNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
	void updateMutatedParams();

private:
    int variableNum;
    float partial;
    float index;
    double w;
};

#endif
