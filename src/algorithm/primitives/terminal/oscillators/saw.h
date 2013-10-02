#ifndef SAWOSCNODE_H
#define SAWOSCNODE_H

#include "../WaveTableNode.h"

class SawOscNode: public WaveTableNode {
public:
    SawOscNode(param* vn, GPMutatableParam* partial, GPMutatableParam* phase);
    ~SawOscNode();

	// node overrides
    SawOscNode* get_copy();
    void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
	
	// WaveTable overrides
	void makeAddAllWaveTables(double sampleRate, unsigned overSamp, unsigned constantRatioLimit, double baseFreq, double topFreq);
    void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);

    // optional overrides
	void update_mutated_params();

private:
};

#endif
