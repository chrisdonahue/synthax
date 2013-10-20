#ifndef SWITCHNODE_H
#define SWITCHNODE_H

#include "../../GPNode.h"

class SwitchNode: public GPNode {
public:
    SwitchNode(GPNode* mod, GPNode* sigone, GPNode* sigtwo);
    ~SwitchNode();

	// overrides
    SwitchNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
	void updateMutatedParams();

private:
};

#endif
