#ifndef TERMINAL_LFO_H
#define TERMINAL_LFO_H

#include "../../node.h"
#include "../super/lfo.h"

namespace synthax{namespace node{namespace terminal{
	class lfo : public synthax::node::super::lfo {
	public:
		lfo(param* rate);
		~lfo();

		// overrides
		lfo* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif
