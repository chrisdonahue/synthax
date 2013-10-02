#include "AMNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

AMNode::AMNode(param* vn, GPMutatableParam* p, GPMutatableParam* o, GPMutatableParam* a, node* mod) {
    assert(vn->is_unmutatable() && vn->is_discrete());
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(p);
    params.push_back(o);
    params.push_back(a);

    descendants.push_back(mod);
    arity = 1;

    symbol = "am";
}

AMNode::~AMNode() {
}

/*
    =========
    OVERRidES
    =========
*/

AMNode* AMNode::get_copy() {
    return new AMNode(params[0]->get_copy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy(), mutatableParams[3]->getCopy(), descendants[0] == NULL ? NULL : descendants[0]->getCopy());
}

void AMNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = (offset + alpha * buffer[i]) * sin (w * (sampleTimes[i]) * (constantVariables[variableNum]));
    }
}

void AMNode::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    w = 2.0 * M_PI * partial;
	
	// update AM params
    offset = params[2]->get_cvalue();
    alpha = params[3]->get_cvalue();
    
    // minimum/maximum constant and declared in constructor
    intervalMultiply(&minimum, &maximum, descendants[0]->minimum, descendants[0]->maximum, alpha, alpha);
    intervalAdd(&minimum, &maximum, minimum, maximum, offset, offset);
}
