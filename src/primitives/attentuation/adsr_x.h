#ifndef ADSR_X_H
#define ADSR_X_H

#include "../base/adsr_b.h"

namespace synthax{namespace primitive{namespace envelope{
	class adsr_x : public base::adsr_b {
	public:
		// construction
		adsr_x(param* del, param* atk, param* atkh, param* dec, param* sus, param* sush, param* rel, node* signal);
		~adsr_x();

		// overrides
		adsr_x* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif