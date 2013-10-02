#ifndef ENVELOPE_PIECEWISE_LINEAR_H
#define ENVELOPE_PIECEWISE_LINEAR_H

#include "../super/piecewise_linear.h"

namespace synthax{namespace primitive{namespace envelope{
	class piecewise_linear: public synthax::primitive::super::piecewise_linear {
	public:
		piecewise_linear(param* splinetype, GPMutatableParam* numpoints, std::vector<GPMutatableParam*>* pointsOrParams, node* signal);
		~piecewise_linear();

		// overrides
		piecewise_linear* get_copy();
		void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

	private:
	};
}}}

#endif