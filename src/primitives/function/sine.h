#ifndef SINE_H
#define SINE_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace function{
	class sine: public node {
	public:
		sine(node* zero);
		~sine();

		// overrides
		sine* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
	};
}}}

#endif
