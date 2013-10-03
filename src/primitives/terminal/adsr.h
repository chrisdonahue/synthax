#ifndef ADSR_H
#define ADSR_H

#include "../base/adsr_b.h"

namespace synthax{namespace primitive{namespace terminal{
	class adsr : public base::adsr_b {
	public:
		// construction
		adsr(param* del, param* atk, param* atkh, param* dec, param* sus, param* sush, param* rel);
		~adsr();

		// overrides
		adsr* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif