#ifndef TERMINAL_PIECEWISE_LINEAR_H
#define TERMINAL_PIECEWISE_LINEAR_H

#include "../super/piecewise_linear.h"

namespace synthax{namespace node{namespace terminal{
	class piecewise_linear : public synthax::node::super::piecewise_linear {
	public:
		piecewise_linear(param* splinetype, GPMutatableParam* numpoints, std::vector<GPMutatableParam*>* pointsOrParams);
		~piecewise_linear();

		// overrides
		piecewise_linear* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);


	private:
	};
}}}

#endif