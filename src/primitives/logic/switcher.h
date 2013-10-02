#ifndef SWITCHER_H
#define SWITCHER_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace logic{
	class switcher: public node {
	public:
		switcher(node* mod, node* sigone, node* sigtwo);
		~switcher();

		// overrides
		switcher* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
	};
}}}

#endif