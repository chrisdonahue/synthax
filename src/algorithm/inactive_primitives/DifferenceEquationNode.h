/*
  ==============================================================================

    DifferenceEquationNode.h
    Created: 6 Feb 2013 11:05:21am
    Author:  cdonahue

  ==============================================================================
*/

#ifndef DIFFERENCEEQUATION_H
#define DIFFERENCEEQUATION_H

#include "../node.h"

class DifferenceEquationNode: public node {
public:
    DifferenceEquationNode(unsigned m, unsigned n, random* r, bool erc, param* z, GPMutatableParam* p, node* signal);
    DifferenceEquationNode(std::vector<param*>& xcoef, std::vector<GPMutatableParam*>& ycoef, node* signal);
    ~DifferenceEquationNode();

	// overrides
    DifferenceEquationNode* get_copy();
	void prepare_to_play();
    void evaluateBlock(unsigned fn, double* t, unsigned nv, double* v, double* min, double* max, unsigned n, float* buffer);
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);
	void set_render_info(float sr, unsigned block_size, float max_frame_start_time);
	void update_mutated_params();
    void to_string(std::stringstream& ss);

private:
    // difference equation zeroes
    unsigned numXCoefficients;
    std::vector<param*> xcoefficients;
    float* xcoefs;
    float* x;

    // difference equation poles
    unsigned numYCoefficients;
    std::vector<param*> ycoefficients;
    float* ycoefs;
    float* y;
};

#endif
