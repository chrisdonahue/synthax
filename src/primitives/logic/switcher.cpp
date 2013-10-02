#include "switcher.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

synthax::primitive::logic::switcher::switcher(node* mod, node* sigone, node* sigtwo) {
    arity = 3;
    descendants.push_back(mod);
    descendants.push_back(sigone);
    descendants.push_back(sigtwo);

    symbol = "switch";
}

synthax::primitive::logic::switcher::~switcher() {
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::logic::switcher* synthax::primitive::logic::switcher::get_copy() {
    return new switcher(descendants[0] == NULL ? NULL : descendants[0]->get_copy(), descendants[1] == NULL ? NULL : descendants[1]->get_copy(), descendants[2] == NULL ? NULL : descendants[2]->get_copy());
}

void synthax::primitive::logic::switcher::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    descendants[0]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
    descendants[1]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[0]);
    descendants[2]->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, descendant_buffers[1]);

    for (unsigned i = 0; i < numSamples; i++) {
        if (buffer[i] <= 0) {
            buffer[i] = descendant_buffers[0][i];
        }
        else {
            buffer[i] = descendant_buffers[1][i];
        }
    }
}

void synthax::primitive::logic::switcher::update_mutated_params() {
    node::update_mutated_params();

    // update min/max values from descendants
    float signalOneMin = descendants[1]->minimum;
    float signalOneMax = descendants[1]->maximum;
    float signalTwoMin = descendants[2]->minimum;
    float signalTwoMax = descendants[2]->maximum;
    minimum = signalOneMin < signalTwoMin ? signalOneMin : signalTwoMin;
    maximum = signalOneMax > signalTwoMax ? signalOneMax : signalTwoMax;
}