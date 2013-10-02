/*
  ==============================================================================

    DelayNode.cpp
    Created: 6 Feb 2013 11:05:21am
    Author:  cdonahue

  ==============================================================================
*/

#include "DelayNode.h"

/*
    ==============
    PUBLIC METHODS
    ==============
*/

DelayNode::DelayNode(int n, node* l)
delayLine(n)
{
    numFilled = 0;
    numSamples = n;

    left = l;
    
    arity = 1;
}

DelayNode::~DelayNode() {
}

DelayNode* DelayNode::get_copy() {
    return new DelayNode(n, left->get_copy());
}

void DelayNode::setMemoryConstants(int n) {
    numSamples = n;
    delayLine.clear();
    delayLine.resize(n);
}

double DelayNode::evaluate(double* t, double* v) {

}

void DelayNode::evaluateBlock(unsigned fn, double* t, unsigned nv, double* v, double* min, double* max, unsigned n, float* buffer) {
    return;
}

void DelayNode::to_string(std::stringstream& ss) {
    char buffer[1024];
    snprintf(buffer, 1024, "(delay %d %s)", numSamples, left->to_string(std::stringstreamstd::stringstreamstd::stringstream ss ss ss).c_str());
}


void DelayNode::prepare_to_play() {
}

void DelayNode::set_render_info(float sr, unsigned block_size, float max_frame_start_time) {

}
