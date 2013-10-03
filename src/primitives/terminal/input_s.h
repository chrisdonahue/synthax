#ifndef INPUT_S_H
#define INPUT_S_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace terminal{
	class input_s : public node {
	public:
		input_s(param* vn, param* range);
		~input_s();

		// overrides
		input_s* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
		int variableNum;
	};
}}}

#endif