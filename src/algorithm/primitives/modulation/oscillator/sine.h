#ifndef SINFREQOSCNODE_H
#define SINFREQOSCNODE_H

#include "../WaveTableFreqNode.h"

class SinFreqOscNode: public WaveTableFreqNode {
public:
    SinFreqOscNode(param* phase, node* freq);
    ~SinFreqOscNode();

	// node overrides
    SinFreqOscNode* get_copy();
    void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time);
	
	// WaveTable overrides
	void makeAddAllWaveTables(double sampleRate, unsigned overSamp, unsigned constantRatioLimit, double baseFreq, double topFreq);
    void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);

private:
};

#endif
