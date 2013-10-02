#ifndef MIXER_H
#define MIXER_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace logic{
	class mixer : public node {
	public:
		mixer(node* mod, GPNode* sigone, GPNode* sigtwo);
		~mixer();

		// overrides
		mixer* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
		float controlMin;
		float controlMax;
	};
}}}

#endif
