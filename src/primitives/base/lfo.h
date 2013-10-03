#ifndef LFO_H
#define LFO_H

#include "../../node.h"

namespace synthax{namespace primitive{namespace abstract{
	class lfo : public node {
	public:
		// optional overrides
		void update_mutated_params();

	protected:
		float rate;
		double w;
	};
}}}

#endif
