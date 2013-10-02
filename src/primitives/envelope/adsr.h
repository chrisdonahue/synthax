#ifndef ENVELOPE_ADSR_H
#define ENVELOPE_ADSR_H

#include "../super/adsr.h"

namespace synthax{namespace primitive{namespace envelope{
	class adsr : public synthax::primitive::super::adsr {
	public:
		adsr(param* del, GPMutatableParam* atk, GPMutatableParam* atkh, GPMutatableParam* dec, GPMutatableParam* sus, GPMutatableParam* sush, GPMutatableParam* rel, node* signal);
		~adsr();

		// overrides
		adsr* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif