#ifndef ADSR_B_H
#define ADSR_B_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace base{
	class adsr_b : public node {
	public:
		// node class overrides
		void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void update_mutated_params();

		// forced subclass overrides
		virtual adsr_b* get_copy() = 0;
		virtual void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) = 0;

		// class specific
		void fillFromParams();

	protected:
		double sampleRate;
		bool releaseFinished;
		unsigned framesInEnvelope;
		float* envelope;

		double delay;
		unsigned delayFrames;
		double attack;
		unsigned attackFrames;
		double decay;
		unsigned decayFrames;
		double sustain;
		unsigned sustainFrames;
		double release;
		unsigned releaseFrames;
		double attackheight;
		double sustainheight;
	};
}}}

#endif
