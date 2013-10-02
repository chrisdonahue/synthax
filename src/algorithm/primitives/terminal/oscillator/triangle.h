#ifndef TRIANGLEOSCNODE_H
#define TRIANGLEOSCNODE_H

#include "../WaveTableNode.h"

class TriangleOscNode: public WaveTableNode {
public:
    TriangleOscNode(param* vn, GPMutatableParam* partial, GPMutatableParam* phase);
    ~TriangleOscNode();

	// node overrides
    TriangleOscNode* get_copy();
    void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
	
	// WaveTable overrides
	void makeAddAllWaveTables(double sampleRate, unsigned overSamp, unsigned constantRatioLimit, double baseFreq, double topFreq);
    void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
