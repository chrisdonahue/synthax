#include "input_static.h"

/*
    ============
    construction
    ============
*/

synthax::primitive::terminal::input_static::input_static(param* vn, param* range) {
    assert(vn->is_unmutatable());
    variableNum = vn->get_dvalue();
    params.push_back(vn);

    assert(range->is_unmutatable());
    minimum = range->get_min();
    maximum = range->get_max();
    params.push_back(range);

    arity = 0;

    symbol = "input_s";
}

synthax::primitive::terminal::input_static::~input_static() {
}

/*
    =========
    overrides
    =========
*/

synthax::primitive::terminal::input_static* synthax::primitive::terminal::input_static::get_copy() {
    return new input_static(params[0]->get_copy(), params[1]->get_copy());
}

void synthax::primitive::terminal::input_static::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    firstFrameNumber;
    sampleTimes;
    numConstantVariables;

    for (unsigned i = 0; i < numSamples; i++) {
        buffer[i] = constantVariables[variableNum];
    }
}
