#ifndef INPUT_STATIC_H
#define INPUT_STATIC_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace terminal{
	class input_static : public node {
	public:
		input_static(param* vn, param* range);
		~input_static();

		// overrides
		input_static* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
		int variableNum;
	};
}}}

#endif
