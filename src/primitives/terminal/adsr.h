#ifndef TERMINALADSR_H
#define TERMINALADSR_H

#include "../../node.h"
#include "../super/adsr.h"

namespace synthax{namespace primitive{namespace terminal{
	class adsr : public synthax::primitive::abstract::adsr {
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
