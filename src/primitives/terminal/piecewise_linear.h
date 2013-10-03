#ifndef TERMINAL_PIECEWISE_LINEAR_H
#define TERMINAL_PIECEWISE_LINEAR_H

#include "../abstract/piecewise_linear.h"

namespace synthax{namespace primitive{namespace terminal{
	class piecewise_linear : public synthax::primitive::abstract::piecewise_linear {
	public:
		piecewise_linear(param* splinetype, param* numpoints, std::vector<param*>* pointsOrParams);
		~piecewise_linear();

		// overrides
		piecewise_linear* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);


	private:
	};
}}}

#endif