#ifndef VALUESTATICNODE_H
#define VALUESTATICNODE_H

#include "../../GPNode.h"

class ValueStaticNode: public GPNode {
public:
    ValueStaticNode(GPMutatableParam* vn, GPMutatableParam* range);
    ~ValueStaticNode();

	// overrides
    ValueStaticNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

private:
    int variableNum;
};

#endif
