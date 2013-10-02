#ifndef SILENCE_H
#define SILENCE_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace terminal{
	class silence : public node {
	public:
		silence();
		~silence();

		// overrides
		silence* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif
