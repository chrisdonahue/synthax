#include "lfo.h"

void synthax::primitive::super::lfo::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    rate = params[0]->get_value();
    w = 2.0 * M_PI * rate;
	
    // minimum/maximum constant and declared in constructor
}
