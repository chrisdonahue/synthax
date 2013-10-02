/*
  ==============================================================================

    FilterNode.cpp
    Created: 6 Feb 2013 11:05:21am
    Author:  cdonahue

  ==============================================================================
*/

#include "FilterNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

FilterNode::FilterNode(char* t, unsigned o, unsigned fpc, double sr, int vn, param* cfmultmin, param* cfmultmax, param* bwq, node* signal, node* center) :
    params()
{
    type = t;
    order = o;
    fadeParameterChanges = fpc;
    sampleRate = sr;
    nyquist = sampleRate/2;

    variableNum = vn;

    params.push_back(cfmultmin);
    params.push_back(cfmultmax);
    params.push_back(bwq);


    if (strcmp(t, "lp") == 0) {
        
    }
    else if (strcmp(t, "hp") == 0) {
    
    }
    else if (strcmp(t, "bp") == 0) {
        
    }
    else if (strcmp(t, "bs") == 0) {
    
    }

    arity = 2;
    descendants.push_back(signal);
    descendants.push_back(center);

    fillFromParams();
}

FilterNode::~FilterNode() {
    delete filter;
}

/*
    =========
    OVERRidES
    =========
*/

FilterNode* FilterNode::get_copy() {
    return new FilterNode(type, order, fadeParameterChanges, sampleRate, variableNum, params[0]->get_copy(), params[1]->get_copy(), params[2]->get_copy(), descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->get_copy(), NULL);
}

void FilterNode::prepare_to_play() {

}

void FilterNode::evaluateBlock(unsigned fn, double* t, unsigned nv, double* v, double* min, double* max, unsigned n, float* buffer) {
    // evaluate signal
    descendants[0]->evaluateBlock(fn, t, nv, v, min, max, n, buffer);
    float* audioData[1];
    audioData[0] = buffer;

    // evaluate center frequency signal
    float* cfbuffer = (float*) malloc(sizeof(float) * n);
    double cfmin = std::numeric_limits<double>::min();
    double cfmax = std::numeric_limits<double>::max();
    descendants[1]->evaluateBlock(fn, t, nv, v, &cfmin, &cfmax, n, cfbuffer);

    // create mapping from center frequency signal to center frequency multiplier
    double cfm = 0;
    double cfb = 0;
    continuousMapRange(cfmin, cfmax, centerFrequencyMultiplierMin, centerFrequencyMultiplierMax, &cfm, &cfb);

    // get pointer to variable we are using
    double* currentIndex = v + variableNum;

    // reset filter on init
    if (fn == 0) {
        filter->reset();
        params[2] = (*currentIndex) * (cfbuffer[0] * cfm + cfb);
        params[3] = bandwidthQuality;
        filter->setParams(params);
    }

    /*
    float* bwqbuffer = (float*) malloc(sizeof(float) * n);
    double bwqmin = std::numeric_limits<double>::min();
    double bwqmax = std::numeric_limits<double>::max();
    descendants[2]->evaluateBlock(fn, t, nv, v, &bwqmin, &bwqmax, n, bwqbuffer);
    double bwqscale = (bandwidthQualityMax - bandwidthQualityMin) / (bwqmax - bwqmin);
    */

    // TODO: calculate min/max for lopass/hipass


    // update filter params
    params[2] = (*currentIndex) * (cfbuffer[n-1] * cfm + cfb);
    params[3] = bandwidthQuality;

   /* 
    if (params[2] < 1.0 || params[2] >= params[0] / 2) {
	std::cout << "[" << cfmin << ", " << cfmax << "] -> [" << centerFrequencyMultiplierMin << ", " << centerFrequencyMultiplierMax << "]" << std::endl;
	std::stringstream ss;
	descendants[1]->to_string(ss);
	std::cout << ss.str() << std::endl;
        std::cout << params[2] << ", " << cfbuffer[n-1] << ", " << cfm << ", "<< cfb << std::endl;
    }
    if (cfm > 0 && cfm <= 0.01) {
        std::cout << "WOW RANGE IS CLOSE" << std::endl;
	std::cout << "[" << cfmin << ", " << cfmax << "] -> [" << centerFrequencyMultiplierMin << ", " << centerFrequencyMultiplierMax << "]" << std::endl;
	std::stringstream ss;
	descendants[1]->to_string(ss);
	std::cout << ss.str() << std::endl;
        std::cout << params[2] << ", " << cfbuffer[n-1] << ", " << cfm << ", "<< cfb << std::endl;
        std::cout << "------------" << std::endl;
    }
    */

    for (unsigned i = 0; i < n; i++) {
        if (cfbuffer[i] < -1.0 || cfbuffer[i] > 1.0) {
            std::cout << "SIN IS MESSED UP" << std::endl;
            std::cout << buffer[i] << std::endl;
        }
    }

    filter->setParams(params);
    filter->process(n, audioData);

    for (unsigned i = 0; i < n; i++) {
        if (buffer[i] < -1.0 || buffer[i] > 1.0) {
            std::cout << "[" << cfmin << ", " << cfmax << "] -> [" << centerFrequencyMultiplierMin << ", " << centerFrequencyMultiplierMax << "]" << std::endl;
            std::stringstream ss;
            descendants[1]->to_string(true, ss);
            std::cout << ss.str() << std::endl;
            std::cout << params[2] << ", " << params[3] << ", " << cfbuffer[n-1] << ", " << cfm << ", "<< cfb << std::endl;
            std::cout << "FILTER IS MESSED UP" << std::endl;
            std::cout << buffer[i] << std::endl;
            exit(-1);
        }
    }

    //free(bwqbuffer);
    free(cfbuffer);
}

void FilterNode::set_render_info(float sr, unsigned block_size, float max_frame_start_time) {

}

void FilterNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {

}

void FilterNode::update_mutated_params() {
    fillFromParams();

    // call on descendants
    descendants[0]->update_mutated_params();
    descendants[1]->update_mutated_params();
}

void FilterNode::to_string(std::stringstream& ss) {
    ss << "(" << type;
    ss << " [";
    params[0]->to_string(printRange, ss);
    ss <<  ", ";
    params[1]->to_string(printRange, ss);
    ss << "] ";
    params[2]->to_string(printRange, ss);
    ss << " ";
    descendants[0]->to_string(printRange, ss);
    ss << " ";
    descendants[1]->to_string(printRange, ss);
    ss << ")";
}

/*
    ==============
    CLASS SPECIFIC
    ==============
*/

void FilterNode::fillFromParams() {
    // update mutated params
    centerFrequencyMultiplierMin = params[0]->get_value();
    centerFrequencyMultiplierMax = params[1]->get_value();
    if (centerFrequencyMultiplierMax < centerFrequencyMultiplierMin) {
        centerFrequencyMultiplierMin = centerFrequencyMultiplierMax;
        centerFrequencyMultiplierMax = centerFrequencyMultiplierMin;
    }
    bandwidthQuality = params[2]->get_value();
}
