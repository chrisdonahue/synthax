#ifndef FMINODE_H
#define FMINODE_H

#include "../../GPNode.h"

class FMINode: public GPNode {
public:
    FMINode(GPMutatableParam*, GPMutatableParam*, GPMutatableParam*, GPMutatableParam*, GPMutatableParam*, GPNode*);
    ~FMINode();

	// overrides
    FMINode* getCopy();
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
	float mf_ratio;
	float i_low;
    float i_high;

	// calculated
    double cf_mult;
	double mf_mult;
	double i_m;
	double i_b;
};

#endif
