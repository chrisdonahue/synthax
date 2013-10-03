#ifndef ENVELOPE_ADSR_H
#define ENVELOPE_ADSR_H

#include "../base/adsr.h"

namespace synthax{namespace primitive{namespace envelope{
	class adsr : public synthax::primitive::base::adsr {
	public:
		adsr(param* del, param* atk, param* atkh, param* dec, param* sus, param* sush, param* rel, node* signal);
		~adsr();

		// overrides
		adsr* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif