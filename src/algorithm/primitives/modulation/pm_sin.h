#ifndef PMNODE_H
#define PMNODE_H

#include "../../node.h"

class PMNode: public node {
public:
    PMNode(param* vn, GPMutatableParam* p, GPMutatableParam* i, node* mod);
    ~PMNode();

	// overrides
    PMNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
	void update_mutated_params();

private:
    int variableNum;
    float partial;
    float index;
    double w;
};

#endif
