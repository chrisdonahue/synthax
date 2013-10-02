/*
  ==============================================================================

    OscilNode.cpp
    Author:  cdonahue

  ==============================================================================
*/

#include "OscilNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

OscilNode::OscilNode(bool terminal, param* vn, param* p, param* i, node* mod) {
    terminalOscil = terminal;
    assert(!(vn->isMutatable) && !(vn->isContinuous));
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(p);

    if (terminalOscil) {
        arity = 0;
    }
    else {
        params.push_back(i);
        descendants.push_back(mod);
        arity = 1;
    }
    
    minimum = -1;
    maximum = 1;
}

OscilNode::~OscilNode() {
}

/*
    =========
    OVERRidES
    =========
*/

OscilNode* OscilNode::get_copy() {
    if (terminalOscil)
        return new OscilNode(terminalOscil, params[0]->get_copy(), params[1]->get_copy(), NULL, NULL);
    else
        return new OscilNode(terminalOscil, params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy());
}

void OscilNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    if (terminalOscil) {
        for (unsigned i = 0; i < numSamples; i++) {
            // produce a sine wave at frequency *currentIndex * p
            buffer[i] = sin(w * (sampleTimes[i]) * (constantVariables[variableNum]));
        }
    }
    else {
        descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
        for (unsigned i = 0; i < numSamples; i++) {
            // equivalent to chowning 1973 FM synthesis assuming buffer is a sine wave
            buffer[i] = sin( (w * (sampleTimes[i]) * (constantVariables[variableNum])) + (index * buffer[i]));
        }
    }
}

void OscilNode::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    w = 2.0 * M_PI * partial;
	
	// update index of modulation and descendant if this is an FM oscillator
    if (!terminalOscil) {
        index = params[2]->get_cvalue();
    }
    
    // minimum/maximum constant and declared in constructor
}

void OscilNode::to_string(std::stringstream& ss) {
    if (terminalOscil) {
        ss << "(osc ";
        params[0]->to_string(ss);
        ss << " ";
        params[1]->to_string(ss);
        ss << ")";
    }
    else {
        ss << "(fm "; 
        params[0]->to_string(ss);
        ss << " ";
        params[1]->to_string(ss);
        ss << " ";
        params[2]->to_string(ss);
        ss << " ";
        descendants[0]->to_string(ss);
        ss << ")";
    }
}
