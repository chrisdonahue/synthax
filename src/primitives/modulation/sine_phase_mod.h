#ifndef SINE_PHASE_MOD_H
#define SINE_PHASE_MOD_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace modulation{
	class sine_phase_mod : public node {
	public:
		sine_phase_mod(param* vn, param* p, param* i, node* mod);
		~sine_phase_mod();

		// overrides
		sine_phase_mod* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
		int variableNum;
		float partial;
		float index;
		double w;
	};
}}}

#endif