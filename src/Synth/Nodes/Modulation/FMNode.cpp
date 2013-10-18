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

void FMNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
		double mf = buffer[i] * freq_m + freq_b;
		buffer[i] = (float) sin((cf_mult * sampleTimes[i] * constantVariables[variableNum]) + ((mf_outer_mult * mf) * (mf_inner_mult * sampleTimes[i] * mf)));
    }
}

void FMNode::setRenderInfo(float sr, unsigned blockSize, unsigned maxNumFrames, float maxTime) {
    sample_rate = sr;
    GPNode::setRenderInfo(sr, blockSize, maxNumFrames, maxTime);
}

void FMNode::updateMutatedParams() {
    GPNode::updateMutatedParams();

	// get params
    partial = mutatableParams[1]->getValue();
	mf_low = mutatableParams[2]->getValue();
	mf_high = mutatableParams[3]->getValue();
	index = mutatableParams[4]->getValue();

	// confirm params
	float nyquist_rate = sample_rate / 2;
	assert(mf_low >= 0 && mf_high <= nyquist_rate);

	// precompute for efficiency
    cf_mult = (2.0 * M_PI * partial) / sample_rate;
	mf_outer_mult = (2.0 * M_PI * index);
	mf_inner_mult = (2.0 * M_PI) / sample_rate;
    
    // minimum/maximum constant and declared in constructor
    continuousMapRange((double) descendants[0]->minimum, (double) descendants[0]->maximum, mf_low, mf_high, &freq_m, &freq_b);
}
