/*
  ==============================================================================

    OscilNode.h
    Author:  cdonahue

  ==============================================================================
*/

#ifndef OSCILNODE_H
#define OSCILNODE_H

#include "../../GPNode.h"

class OscilNode: public GPNode {
public:
    OscilNode(bool terminal, GPMutatableParam* vn, GPMutatableParam* p, GPMutatableParam* i, GPNode* mod);
    ~OscilNode();

	// overrides
    OscilNode* getCopy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);
    void toString(std::stringstream& ss);

    // optional overrides
	void updateMutatedParams();

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
