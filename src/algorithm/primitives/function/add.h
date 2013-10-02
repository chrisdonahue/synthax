#ifndef ADD_H
#define ADD_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace function{
	class add : public node {
	public:
		add(node* zero, GPNode* one);
		~add();

		// overrides
		add* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
	};
}}}

#endif