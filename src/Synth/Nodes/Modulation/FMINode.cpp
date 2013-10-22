#include "FMINode.h"

/*
    ========================
    CONSTRUCTION/DESTRUCTION
    ========================
*/

FMINode::FMINode(GPMutatableParam* vn, GPMutatableParam* p, GPMutatableParam* m_ratio, GPMutatableParam* i_center, GPMutatableParam* i_radius, GPNode* mod) {
    assert(vn->isUnmutatable() && vn->isDiscrete());
	assert(i_radius->getMin() >= 0);

	mutatableParams.push_back(vn);
	mutatableParams.push_back(p);
	mutatableParams.push_back(m_ratio);
    mutatableParams.push_back(i_center);
    mutatableParams.push_back(i_radius);

    descendants.push_back(mod);
    arity = 1;
    
    minimum = -1;
    maximum = 1;

    symbol = "fm_i";
}

FMINode::~FMINode() {
}

/*
    =========
    OVERRIDES
    =========
*/

FMINode* FMINode::getCopy() {
    return new FMINode(mutatableParams[0]->getCopy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy(), mutatableParams[3]->getCopy(), mutatableParams[4]->getCopy(), descendants[0] == NULL ? NULL : descendants[0]->getCopy());
}

void FMINode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, constantValues, variableValues, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
		double index = buffer[i] * i_m + i_b;
		float t = sampleTimes[i];
		buffer[i] = (float) cos((cf_mult * t * constantValues[variableNum]) + index * (mf_mult * constantValues[variableNum] * t));
    }
}

void FMINode::setRenderInfo(float sr, unsigned blockSize, unsigned maxNumFrames, float maxTime) {
    sample_rate = sr;
    GPNode::setRenderInfo(sr, blockSize, maxNumFrames, maxTime);
}

void FMINode::updateMutatedParams() {
    GPNode::updateMutatedParams();

	// get params
	variableNum = mutatableParams[0]->getDValue();
    partial = mutatableParams[1]->getValue();
	mf_ratio = mutatableParams[2]->getValue();
	float i_center = mutatableParams[3]->getValue();
	float i_radius = mutatableParams[4]->getValue();
	i_low = i_center - i_radius;
	i_high = i_center + i_radius;

	// precompute for efficiency
    cf_mult = (2.0 * M_PI * partial);
	mf_mult = (2.0 * M_PI * mf_ratio);
    
    // minimum/maximum constant and declared in constructor
    continuousMapRange((double) descendants[0]->minimum, (double) descendants[0]->maximum, i_low, i_high, &i_m, &i_b);
}
