#include "FMNode.h"

/*
    ========================
    CONSTRUCTION/DESTRUCTION
    ========================
*/

FMNode::FMNode(GPMutatableParam* vn, GPMutatableParam* p, GPMutatableParam* mf_low, GPMutatableParam* mf_high, GPMutatableParam* i, GPNode* mod) {
    assert(vn->isUnmutatable() && vn->isDiscrete());

	mutatableParams.push_back(vn);
	mutatableParams.push_back(p);
	mutatableParams.push_back(mf_low);
    mutatableParams.push_back(mf_high);
    mutatableParams.push_back(i);

    descendants.push_back(mod);
    arity = 1;
    
    minimum = -1;
    maximum = 1;

    symbol = "fm";
}

FMNode::~FMNode() {
}

/*
    =========
    OVERRIDES
    =========
*/

FMNode* FMNode::getCopy() {
    return new FMNode(mutatableParams[0]->getCopy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy(), mutatableParams[3]->getCopy(), mutatableParams[4]->getCopy(), descendants[0] == NULL ? NULL : descendants[0]->getCopy());
}

void FMNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, constantValues, variableValues, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
		double mf = buffer[i] * mf_m + mf_b;
		double t = (double) sampleTimes[i];
		buffer[i] = (float) cos((cf_mult * t * constantValues[variableNum]) + index * (mf_mult * mf * t));
    }
}

void FMNode::setRenderInfo(float sr, unsigned blockSize, unsigned maxNumFrames, float maxTime) {
    sample_rate = sr;
    GPNode::setRenderInfo(sr, blockSize, maxNumFrames, maxTime);
}

void FMNode::updateMutatedParams() {
    GPNode::updateMutatedParams();

	// get params
	variableNum = mutatableParams[0]->getDValue();
    partial = mutatableParams[1]->getValue();
	mf_low = mutatableParams[2]->getValue();
	mf_high = mutatableParams[3]->getValue();
	index = mutatableParams[4]->getValue();

	// confirm params
	float nyquist_rate = sample_rate / 2;
	assert(mf_low >= 0 && mf_high <= nyquist_rate);

	// precompute for efficiency
    cf_mult = (2.0 * M_PI * partial);
	mf_mult = (2.0 * M_PI);
    
    // minimum/maximum constant and declared in constructor
    continuousMapRange((double) descendants[0]->minimum, (double) descendants[0]->maximum, mf_low, mf_high, &mf_m, &mf_b);
}
