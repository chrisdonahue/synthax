#ifndef AMNODE_H
#define AMNODE_H

#include "../../node.h"

class AMNode: public node {
public:
    AMNode(param* vn, GPMutatableParam* p, GPMutatableParam* o, GPMutatableParam* a, node* mod);
    ~AMNode();

	// overrides
    AMNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
    int variableNum;
    float partial;
    float offset;
    float alpha;
    double w;
};

#endif
