#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace function{
	class multiply : public node {
	public:
		multiply(node* zero, GPNode* one);
		~multiply();

		// overrides
		multiply* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
	};
}}}

#endif
