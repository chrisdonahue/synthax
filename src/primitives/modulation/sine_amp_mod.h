#ifndef SIN_AMP_MOD_H
#define SIN_AMP_MOD_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace modulation{
	class sin_amp_mod : public node {
	public:
		sin_amp_mod(param* vn, GPMutatableParam* p, GPMutatableParam* o, GPMutatableParam* a, node* mod);
		~sin_amp_mod();

		// overrides
		sin_amp_mod* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

		// optional overrides
		void update_mutated_params();

	private:
		int variableNum;
		float partial;
		float offset;
		float alpha;
		double w;
	};
}}}

#endif