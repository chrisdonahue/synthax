/*
  ==============================================================================

    DifferenceEquationNode.cpp
    Created: 6 Feb 2013 11:05:21am
    Author:  cdonahue

  ==============================================================================
*/

#include "DifferenceEquationNode.h"

/*
    ==============
    PUBLIC METHODS
    ==============
*/

DifferenceEquationNode::DifferenceEquationNode(unsigned m, unsigned n, random* r, bool erc, param* z, GPMutatableParam* p, node* signal) :
    xcoefficients(), ycoefficients()
{
    // allocate zero buffer
    numXCoefficients = m;
    x = (float*) calloc(numXCoefficients, sizeof(float));
    xcoefs = (float*) calloc(numXCoefficients, sizeof(float));

    // allocate pole buffer
    numYCoefficients = n;
    y = (float*) calloc(numYCoefficients, sizeof(float));
    ycoefs = (float*) calloc(numYCoefficients, sizeof(float));

    // make mutatable params for x coefficients
    for (unsigned i = 0; i < numXCoefficients; i++) {
        param* copy = z->get_copy();
        if (erc)
            copy->ephemeral_random(r);
        xcoefs[i] = copy->get_cvalue();
        xcoefficients.push_back(copy);
        params.push_back(copy);
    }
    delete z;

    // make mutatable params for y coefficients
    for (unsigned i = 0; i < numYCoefficients; i++) {
        param* copy = p->get_copy();
        if (ephemeralRandomConstants)
            copy->ephemeral_random(rng);
        ycoefs[i] = copy->get_cvalue();
        ycoefficients.push_back(copy);
        params.push_back(copy);
    }
    delete p;

    // add signal to descendants
    arity = 1;
    descendants.push_back(signal);
}

DifferenceEquationNode::DifferenceEquationNode(std::vector<param*>& xcoef, std::vector<GPMutatableParam*>& ycoef, node* signal) {
    numXCoefficients = xcoef.size();
    xcoefficients = xcoef;
    x = (float*) calloc(numXCoefficients, sizeof(float));

    numYCoefficients = ycoef.size();
    ycoefficients = ycoef;
    y = (float*) calloc(numYCoefficients, sizeof(float));

    for (unsigned i = 0; i < xcoefficients.size(); i++) {
        params.push_back(xcoefficients[i]);
    }

    for (unsigned i = 0; i < ycoefficients.size(); i++) {
        params.push_back(ycoefficients[i]);
    }

    descendants.push_back(signal);
}

DifferenceEquationNode::~DifferenceEquationNode() {
    free(xcoefs);
    free(x);
    free(ycoefs);
    free(y);
}

DifferenceEquationNode* DifferenceEquationNode::get_copy() {
    std::vector<param*> xcoefcopies(numXCoefficients);
    for (unsigned i = 0; i < numXCoefficients; i++) {
        xcoefcopies[i] = xcoefficients[i]->get_copy();
    }
    std::vector<param*> ycoefcopies(numYCoefficients);
    for (unsigned i = 0; i < numYCoefficients; i++) {
        ycoefcopies[i] = ycoefficients[i]->get_copy();
    }
    return new DifferenceEquationNode(xcoefcopies, ycoefcopies, descendants[0]->get_copy();
}

void DifferenceEquationNode::evaluateBlock(unsigned fn, double* t, unsigned nv, double* v, double* min, double* max, unsigned n, float* buffer) {
    descendants[0]->evaluateBlock(fn, t, nv, v, min, max, n, buffer);

    for (unsigned i = 0; i < n; i++) {
        unsigned j;
        unsigned k;
        for (j = 1; j < numXCoefficients; j++) {
            x[j] = x[j-1];
        }
        x[0] = buffer[i];
        for (k = 1; k < numYCoefficients; j++) {
            y[k] = y[k-1];
        }
        buffer[i] = 0;
        for (j = 0; j < numXCoefficients; j++) {
            buffer[i] += xcoefs[j] * x[j];
        }
        for (k = 1; k < numYCoefficients; k++) {
            buffer[i] += ycoefs[k] * y[k];
        }
        y[0] = buffer[i];
    }
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 1;
    }
        *min = min;
*max = max;
}

void DifferenceEquationNode::to_string(std::stringstream& ss) {
    ss << "(iirfilter z" << numXCoefficients << ":";
    for (unsigned i = 0; i < numXCoefficients; i++) {
        ss << " " << xcoefs[i];
    }
    ss << " p" << numYCoefficients << ":";
    for (unsigned i = 0; i < numYCoefficients; i++) {
        ss << " " << ycoefs[i];
    }
    descendants[0]->to_string(ss);
    ss << ")";
}

void DifferenceEquationNode::update_mutated_params() {
    for (unsigned i = 0; i < numXCoefficients; i++) {
        xcoefs[i] = xcoefficients[i]->get_cvalue();
    }
    for (unsigned i = 0; i < numYCoefficients; i++) {
        ycoefs[i] = ycoefficients[i]->get_cvalue();
    }

    descendants[0]->update_mutated_params();
}


void DifferenceEquationNode::prepare_to_play() {
}

void DifferenceEquationNode::set_render_info(float sr, unsigned block_size, float max_frame_start_time) {

}
