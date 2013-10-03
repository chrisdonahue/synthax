#ifndef LFO_B_H
#define LFO_B_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace base{
	class lfo_b : public node {
	public:
		// optional overrides
		void update_mutated_params();

	protected:
		float rate;
		double w;
	};
}}}

#endif
