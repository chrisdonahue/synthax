#ifndef NOISENODE_H
#define NOISENODE_H

#include "../../GPNode.h"
#include <list>

class NoiseNode: public GPNode {
public:
    NoiseNode();
    ~NoiseNode();

	// overrides
    NoiseNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, float* constantValues, float* variableValues, float* buffer);

	// class specific
	void whitenoise(float* _fpDstBuffer, unsigned int _uiBufferSize, float _fLevel );

private:
    GPRandom* rng;
    float g_fScale;
    int g_x1;
    int g_x2;

    // whitenoise stuff
};

#endif
