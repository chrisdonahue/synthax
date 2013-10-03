#include "env_lin.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

// points should always have something in it
synthax::primitive::terminal::env_lin::env_lin(param* splinetype, param* numsegments, std::vector<param*>* pointsOrParams)
{
    assert(splinetype->is_unmutatable());
    isPrimitive = (pointsOrParams->size() == 2 && numsegments->is_mutatable());
    assert(isPrimitive || numsegments->is_unmutatable());

    splineType = splinetype->get_dvalue();

    params.push_back(splinetype);
    params.push_back(numsegments);

    if (isPrimitive) {
    }
    else {
        numSegments = numsegments->get_dvalue();
        assert(pointsOrParams->size() == (numSegments * 2) + 1);
    }

    for (unsigned i = 0; i < pointsOrParams->size(); i++) {
        params.push_back(pointsOrParams->at(i));
    }
    delete pointsOrParams;

    arity = 0;

    symbol = "env_lin";
}

synthax::primitive::terminal::env_lin::~env_lin() {
    done_rendering();
}

/*
    =========
    OVERRidES
    =========
*/

synthax::primitive::terminal::env_lin* synthax::primitive::terminal::env_lin::get_copy() {
    // make copies of spline points
    std::vector<param*>* paramCopies = new std::vector<param*>(params.size() - 2);
    for (unsigned i = 2; i < params.size(); i++) {
        paramCopies->at(i - 2) = params[i]->get_copy();
    }

    return new env_lin(params[0]->get_copy(), params[1]->get_copy(), paramCopies);
}

void synthax::primitive::terminal::env_lin::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    // copy envelope into buffer
    for (unsigned bi = 0, ei = firstFrameNumber; bi < numSamples; bi++, ei++) {
        buffer[bi] = envelope[ei];
    }
}