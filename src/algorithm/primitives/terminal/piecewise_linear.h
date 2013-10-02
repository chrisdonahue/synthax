#ifndef SPLINETERMINALNODE_H
#define SPLINETERMINALNODE_H

#include "../../node.h"

class SplineTerminalNode: public node {
public:
    SplineTerminalNode(param* splinetype, GPMutatableParam* numpoints, std::vector<GPMutatableParam*>* pointsOrParams);
    ~SplineTerminalNode();

	// overrides
    SplineTerminalNode* get_copy();
	void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);

    // optional overrides
    void ephemeral_random(random* rng);
	void set_render_info(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
    void done_rendering();
	void update_mutated_params();

	// class specific
    void fillFromParams();

private:
    int splineType;
    int numSegments;
    bool isPrimitive;

    float sampleRate;

    unsigned envelopeSize;
    float* envelope;
};

#endif
