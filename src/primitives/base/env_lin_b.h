#ifndef ENV_LIN_B_H
#define ENV_LIN_B_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace base{
	class env_lin_b : public node {
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