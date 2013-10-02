#ifndef LFO_H
#define LFO_H

#include "../../node.h"

namespace synthax{namespace node{namespace super{
	class lfo : public node {
	public:
		// optional overrides
		void update_mutated_params();

	private:
		float rate;
		double w;
	};
}}}

#endif
