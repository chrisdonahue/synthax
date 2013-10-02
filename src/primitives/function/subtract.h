#ifndef SUBTRACT_H
#define SUBTRACT_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace function{
	class subtract : public node {
	public:
		subtract(node* zero, GPNode* one);
		~subtract();

		// overrides
		subtract* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
	};
}}}

#endif