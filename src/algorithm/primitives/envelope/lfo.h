#ifndef ENVELOPE_LFO_H
#define ENVELOPE_LFO_H

#include "../super/lfo.h"

namespace synthax{namespace primitive{namespace envelope{
	class lfo : public synthax::primitive::super::lfo
	public:
		lfo(param* rate, node* mod);
		~lfo();

		// overrides
		lfo* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif
