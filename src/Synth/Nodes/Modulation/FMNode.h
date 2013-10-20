#ifndef FMNODE_H
#define FMNODE_H

#include "../../GPNode.h"

class FMNode: public GPNode {
public:
    FMNode(GPMutatableParam* vn, GPMutatableParam* partial, GPMutatableParam* mf_low, GPMutatableParam* mf_high, GPMutatableParam* i, GPNode* mod);
    ~FMNode();

	// overrides
    FMNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

    // optional overrides
	void setRenderInfo(float sr, unsigned blockSize, unsigned maxNumFrames, float maxTime);
	void updateMutatedParams();

private:
	// environment params
	float sample_rate;

	// mutatable params
    int variableNum;
    float partial;
	float mf_low;
	float mf_high;
    float index;

	// calculated
    double cf_mult;
	double mf_mult;
	double mf_m;
	double mf_b;
};

#endif
