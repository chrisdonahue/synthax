#ifndef LFO_X_H
#define LFO_X_H

#include "../base/lfo_b.h"

namespace synthax{namespace primitive{namespace attenuation{
	class lfo_x : public base::lfo_b {
	public:
		lfo_x(param* rate, node* mod);
		~lfo_x();

		// overrides
		lfo_x* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif
