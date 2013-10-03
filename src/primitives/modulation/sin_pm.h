#ifndef SIN_PM_H
#define SIN_PM_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace modulation{
	class sin_pm : public node {
	public:
		sin_pm(param* vn, param* p, param* i, node* mod);
		~sin_pm();

		// overrides
		sin_pm* get_copy();
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