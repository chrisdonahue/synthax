#ifndef noise_H
#define noise_H

#include "../../node.h"
#include <list>


namespace synthax{namespace node{namespace terminal{
	class noise : public node {
	public:
		noise();
		~noise();

		// overrides
		noise* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// class specific
		void whitenoise(float* _fpDstBuffer, unsigned int _uiBufferSize, float _fLevel );

	private:
		random* rng;
		float g_fScale;
		int g_x1;
		int g_x2;

		// whitenoise stuff
	};
}}}

#endif
