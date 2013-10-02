#include "MixerNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

MixerNode::MixerNode(node* mod, GPNode* sigone, GPNode* sigtwo) {
    arity = 3;
    descendants.push_back(mod);
    descendants.push_back(sigone);
    descendants.push_back(sigtwo);

    symbol = "mix";
}

MixerNode::~MixerNode() {
}

/*
    =========
    OVERRidES
    =========
*/

MixerNode* MixerNode::get_copy() {
    return new MixerNode(descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->getCopy(), descendants[2] == NULL ? NULL : descendants[2]->getCopy());
}

void MixerNode::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    descendants[1]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[0]);
    descendants[2]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[1]);

	double level_m;
	double level_b;
	float level_one;
	float level_two;
    for (unsigned i = 0; i < numSamples; i++) {
		// map control signal to -1 to 1
        continuousMapRange(-1.0f, 1.0f, controlMin, controlMax, &level_m, &level_b);
        buffer[i] = (descendant_buffers[0][i] * level_one) + (descendantBuffers[1][i] * level_two);
    }
}

void MixerNode::update_mutated_params() {
    node::update_mutated_params();

    // update min/max values from descendants
	controlMin = descendants[0]->minimum;
	controlMax = descendants[1]->maximum;
    float signalOneMin = descendants[1]->minimum;
    float signalOneMax = descendants[1]->maximum;
    float signalTwoMin = descendants[2]->minimum;
    float signalTwoMax = descendants[2]->maximum;
    minimum = signalOneMin < signalTwoMin ? signalOneMin : signalTwoMin;
    maximum = signalOneMax > signalTwoMax ? signalOneMax : signalTwoMax;
}
