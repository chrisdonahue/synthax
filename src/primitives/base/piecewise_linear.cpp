#include "piecewise_linear.h"

void synthax::primitive::base::piecewise_linear::ephemeral_random(random* rng) {
    // if this is a primitive spline then generate its points
    if (isPrimitive) {
        // randomize the number of points and lock it
        params[1]->ephemeral_random(rng);
        numSegments = params[1]->get_dvalue();
        params[1]->set_unmutatable();

        // get copies
        param* ampRangeCopy = params[2]->get_copy();
        ampRangeCopy->set_type("spline_amp");
        param* segmentLengthRangeCopy = params[3]->get_copy();
        segmentLengthRangeCopy->set_type("spline_segment_length");

        // remove and delete range specifiers
        delete params[2];
        delete params[3];
        params.resize(2);

        // create the segments
        for (int i = 0; i < numSegments; i++) {
            param* newSplineAmp = ampRangeCopy->get_copy();
            param* newSplineSegmentLength = segmentLengthRangeCopy->get_copy();
            params.push_back(newSplineAmp);
            params.push_back(newSplineSegmentLength);
        }

        // create the final value
        param* newSplineAmpFinal = ampRangeCopy->get_copy();
        newSplineAmpFinal->set_type("spline_amp_final");
        params.push_back(newSplineAmpFinal);

        // delete copies
        delete ampRangeCopy;
        delete segmentLengthRangeCopy;

        // set as no longer primitive
        isPrimitive = false;
    }

    node::ephemeral_random(rng);
}

void synthax::primitive::base::piecewise_linear::set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    assert(!isPrimitive);
    done_rendering();
    sampleRate = sr;
    envelopeSize = max_frame_number;
    envelope = (float*) malloc(sizeof(float) * envelopeSize);
    node::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
}

void synthax::primitive::base::piecewise_linear::done_rendering() {
    if (prepared_to_render) {
        sampleRate = 0;
        free(envelope);
    }
    node::done_rendering();
}

void synthax::primitive::base::piecewise_linear::update_mutated_params() {
    node::update_mutated_params();

    assert(!isPrimitive);

    // get minimum and maximum value for spline envelope
    float minSplineHeight = params[2]->get_cmin();
    float maxSplineHeight = params[2]->get_cmax();
    for (int i = 4; i < params.size(); i += 2) {
        if (params[i]->get_cmin() < minSplineHeight)
            minSplineHeight = params[i]->get_cmin();
        if (params[i]->get_cmax() > maxSplineHeight)
            maxSplineHeight = params[i]->get_cmax();
    }
    
    // update min/max of terminal Spline 
    minimum = minSplineHeight;
    maximum = maxSplineHeight;
    
    fillFromParams();
}

/*
    ==============
    CLASS SPECIFIC
    ==============
*/

void synthax::primitive::base::piecewise_linear::fillFromParams() {
    if (splineType == 0) {
        unsigned currentFrame = 0;
        unsigned usedPoints = 0;
        float currentLevel = params[2]->get_cvalue();
        while (currentFrame < envelopeSize && usedPoints < numSegments) {
            float transitionLength = params[(usedPoints * 2) + 2 + 1]->get_cvalue();
            float nextLevel = params[(usedPoints * 2) + 2 + 2]->get_cvalue();
            unsigned currentTransitionFrame = 0;
            unsigned numTransitionFrames = (unsigned) (transitionLength * sampleRate);
            // may be infinite if numTransitionFrames is 0 but will never be used in that case
            float slope = (nextLevel - currentLevel) / float(numTransitionFrames);
            while (currentTransitionFrame < numTransitionFrames && currentFrame < envelopeSize) {
                envelope[currentFrame] = currentLevel + currentTransitionFrame * slope;
                currentFrame++;
                currentTransitionFrame++;
            }
            usedPoints++;
            currentLevel = nextLevel;
        }
        while (currentFrame < envelopeSize) {
            envelope[currentFrame] = currentLevel;
            currentFrame++;
        }
    }
    else {
        unsigned currentFrame = 0;
        float currentLevel = params[2]->get_cvalue();
        while (currentFrame < envelopeSize) {
            envelope[currentFrame] = currentLevel;
            currentFrame++;
        }
    }
}