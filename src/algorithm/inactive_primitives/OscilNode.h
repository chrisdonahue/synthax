/*
  ==============================================================================

    OscilNode.h
    Author:  cdonahue

  ==============================================================================
*/

#ifndef OSCILNODE_H
#define OSCILNODE_H

#include "../../node.h"

class OscilNode: public node {
public:
    OscilNode(bool terminal, param* vn, GPMutatableParam* p, GPMutatableParam* i, node* mod);
    ~OscilNode();

	// overrides
    OscilNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);
    void to_string(std::stringstream& ss);

    // optional overrides
	void update_mutated_params();

    enum Parameters {
		SINGEN,
		SAWGEN,
		TRIGEN,
        totalNumParams
    };

private:
    bool terminalOscil;
    float partial;
    int variableNum;
    double w;
    double index;
};

#endif
