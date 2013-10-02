#include "TriangleOscNode.h"

/*
    ========================
    construction/DESTRUCTION
    ========================
*/

TriangleOscNode::TriangleOscNode(param* vn, GPMutatableParam* partial, GPMutatableParam* phase) {
    assert(vn->is_unmutatable() && vn->is_discrete());
    variableNum = vn->get_dvalue();

    params.push_back(vn);
    params.push_back(partial);
    params.push_back(phase);

    arity = 0;
    
    minimum = -1;
    maximum = 1;

    symbol = "triangleosc";
}

TriangleOscNode::~TriangleOscNode() {
}

/*
    ================
    GPNODE OVERRidES
    ================
*/

TriangleOscNode* TriangleOscNode::get_copy() {
    return new TriangleOscNode(params[0]->get_copy(), params[1]->getCopy(), params[2]->getCopy());
}

void TriangleOscNode::set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
	WaveTableNode::set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
}

void TriangleOscNode::update_mutated_params() {
    node::update_mutated_params();

	// update angular frequency constant
    partial = params[1]->get_value();
    phase = params[2]->get_value();
	
    // minimum/maximum constant and declared in constructor
}

/*
    ===================
    WAVETABLE OVERRidES
    ===================
*/

void TriangleOscNode::makeAddAllWaveTables(double sampleRate, unsigned overSamp, unsigned constantRatioLimit, double baseFrequency, double topFrequency) {
    // calc number of harmonics where the highest harmonic baseFreq and lowest alias an octave higher would meet
    double baseFreq = baseFrequency;
    int maxHarms = sampleRate / (3.0 * baseFreq) + 0.5;

    // round up to nearest power of two
    unsigned int v = maxHarms;
    v--;            // so we don't go up if already a power of 2
    v |= v >> 1;    // roll the highest bit into all lower bits...
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;            // and increment to power of 2
    int tableLen = v * 2 * overSamp;  // double for the sample rate, then oversampling

	// for ifft
	double* ar = (double*) malloc(sizeof(double) * tableLen);
	double* ai = (double*) malloc(sizeof(double) * tableLen);

	double topFreq = topFrequency;
    //double topFreq = baseFreq * 2.0 / sampleRate;
    double scale = 0.0;
    for (; maxHarms >= 1; maxHarms >>= 1) {
        defineHarmonics(tableLen, maxHarms, ar, ai);
        scale = WaveTableNode::makeAddWaveTable(tableLen, ar, ai, scale, topFreq);
        topFreq *= 2;
        if (tableLen > constantRatioLimit) // variable table size (constant oversampling but with minimum table size)
            tableLen >>= 1;
    }

    free(ai);
    free(ar);
}

void TriangleOscNode::defineHarmonics(int len, int numHarmonics, double* ar, double* ai) {
    if (numHarmonics > (len >> 1))
        numHarmonics = (len >> 1);
    
    // clear
    for (int idx = 0; idx < len; idx++) {
        ai[idx] = 0;
        ar[idx] = 0;
    }

	// triangle
	float sign = 1;
	for (int idx = 1, jdx = len - 1; idx <= numHarmonics; idx++, jdx--) {
		double temp = idx & 0x01 ? 1.0 / (idx * idx) * (sign = -sign) : 0.0;
		ar[idx] = -temp;
		ar[jdx] = temp;
	}
}
