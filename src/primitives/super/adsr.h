#ifndef ADSR_H
#define ADSR_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace super{
	class adsr: public node {
	public:
		// optional overrides
		void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void update_mutated_params();

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
