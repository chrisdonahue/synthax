#ifndef SIN_AM_H
#define SIN_AM_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace modulation{
	class sin_am : public node {
	public:
		sin_am(param* vn, param* p, param* o, param* a, node* mod);
		~sin_am();

		// overrides
		sin_am* get_copy();
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