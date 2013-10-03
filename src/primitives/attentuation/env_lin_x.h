#ifndef ENV_LIN_X_H
#define ENV_LIN_X_H

#include "../base/env_lin_b.h"

namespace synthax{namespace primitive{namespace attenuation{
	class env_lin_x: public base::env_lin_b {
	public:
		env_lin_x(param* splinetype, param* numpoints, std::vector<param*>* pointsOrParams, node* signal);
		~env_lin_x();

		// overrides
		env_lin_x* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif
