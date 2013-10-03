#ifndef ENV_LIN_H
#define ENV_LIN_H

#include "../base/env_lin_b.h"

namespace synthax{namespace primitive{namespace terminal{
	class env_lin : public base::env_lin_b {
	public:
		env_lin(param* splinetype, param* numpoints, std::vector<param*>* pointsOrParams);
		~env_lin();

		// overrides
		env_lin* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);


	private:
	};
}}}

#endif