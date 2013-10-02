#ifndef COSINE_H
#define COSINE_H

#include "../../node.h"

#include <math.h>

namespace synthax{namespace primitive{namespace function{
	class cosine : public node {
	public:
		cosine(node* zero);
		~cosine();

		// overrides
		cosine* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
	};
}}}

#endif
