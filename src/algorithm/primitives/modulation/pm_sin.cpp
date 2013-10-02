#include "PMNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

PMNode::PMNode(param* vn, GPMutatableParam* p, GPMutatableParam* i, node* mod) {
    assert(vn->is_unmutatable() && vn->is_discrete());
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(p);
    params.push_back(i);

    descendants.push_back(mod);
    arity = 1;
    
    minimum = -1;
    maximum = 1;

    symbol = "pm";
}

PMNode::~PMNode() {
}

/*
    =========
    OVERRidES
    =========
*/

PMNode* PMNode::get_copy() {
    return new PMNode(params[0]->get_copy(), mutatableParams[1]->getCopy(), mutatableParams[2]->getCopy(), descendants[0] == NULL ? NULL : descendants[0]->getCopy());
}

void PMNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    for (unsigned i = 0; i < numSamples; i++) {
        // equivalent to chowning 1973 FM synthesis assuming buffer is a sine wave
        buffer[i] = sin( (w * (sampleTimes[i]) * (constantVariables[variableNum])) + (index * buffer[i]));
    }
}

void PMNode::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    w = 2.0 * M_PI * partial;
	
	// update PM params
    index = params[2]->get_cvalue();
    
    // minimum/maximum constant and declared in constructor
}
