/*
  ==============================================================================

    FilterNode.h
    Created: 6 Feb 2013 11:05:21am
    Author:  cdonahue

  ==============================================================================
*/

#ifndef FILTERNODE_H
#define FILTERNODE_H

#include "../node.h"
#include "../../Dependencies/YorkFilters/filterdesign.h"

class FilterNode: public node {
public:
    FilterNode(unsigned t, unsigned o, unsigned fpc, double sr, int vn, param* cfmultmin, GPMutatableParam* cfmultmax, GPMutatableParam* bwq, node* signal, GPNode* center, GPNode* bandwidth);
    ~FilterNode();

	// overrides
    FilterNode* get_copy();
	void prepare_to_play();
    void evaluateBlock(unsigned fn, double* t, unsigned nv, double* v, double* min, double* max, unsigned n, float* buffer);
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);
	void set_render_info(float sr, unsigned block_size, float max_frame_start_time);
	void update_mutated_params();
    void to_string(std::stringstream& ss);

private:
    unsigned type;
    unsigned order;
    unsigned fadeParameterChanges;
    double sampleRate;
    double nyquist;

    int variableNum;

    double centerFrequencyMultiplierMin;
    double centerFrequencyMultiplierMax;
    double bandwidthQuality;
    double bandwidthQualityMinimum;
    double bandwidthQualityMaximum;

    double maxGain;
};

#endif
