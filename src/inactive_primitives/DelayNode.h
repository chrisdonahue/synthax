/*
  ==============================================================================

    DelayNode.h
    Created: 6 Feb 2013 11:05:21am
    Author:  cdonahue

  ==============================================================================
*/

#ifndef DELAYNODE_H
#define DELAYNODE_H

#include "../node.h"
#include <list>

class DelayNode: public node {
public:
    DelayNode(int n, node* l, node* r);
    ~DelayNode();
    DelayNode* get_copy();

    void setMemoryConstant(int n);
    double evaluate(double* t, double* v);
    void evaluateBlock(unsigned fn, double* t, unsigned nv, double* v, double* min, double* max, unsigned n, float* buffer);
    void to_string(std::stringstream& ss);
    void mutate(GPParams* e);

private:
    int numFilled;
    int numSamples;
    std::list<double> delayLine;
};

#endif
