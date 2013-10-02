#ifndef PIECEWISE_LINEAR_H
#define PIECEWISE_LINEAR_H

#include "../../node.h"

namespace synthax{namespace node{namespace super{
	class piecewise_linear : public node {
	public:
		// optional overrides
		void ephemeral_random(random* rng);
		void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
		void done_rendering();
		void update_mutated_params();

		// class specific
		void fillFromParams();

	protected:
		int splineType;
		int numSegments;
		bool isPrimitive;

		float sampleRate;

		unsigned envelopeSize;
		float* envelope;
	};
}}}

#endif