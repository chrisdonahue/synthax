#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../common/helpers.h"
#include "../common/juce_file_io.h"
#include "../common/parser.h"
#include "../common/random.h"
#include "node.h"
#include "param.h"
#include "primitives.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <string.h>

namespace synthax {
    class algorithm {
    public:
        // construction
        algorithm(node* r, std::string o);
        ~algorithm();
        algorithm* getCopy(std::string neworigin);

        // examination
        void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer);
        std::string to_string(unsigned precision);
        node* get_root();
        bool equals(algorithm* other, unsigned precision);
        node* get_random_network_node(random* r);
        std::vector<param*>* get_all_mutatable_params();

        // helpers
        void trace();
        void prepare_to_render(float sr, unsigned block_size, unsigned max_num_frames, float max_frame_start_time);
        void update_mutated_params();
        void done_rendering();
        void replace_subtree(node* one, GPNode* two);
        void ephemeral_random(random* r);

        // PUBLIC STATE
        int id;
        std::string origin;
        int height;
        double fitness;
        
        // interval
        float minimum;
        float maximum;

        // render state
        bool traced;
        bool prepared_to_render;

    private:
        // private state
        node* root;
        node* render_root;
        std::vector<node*> all_nodes;
        std::vector<param*> all_mutatable_params;
    };

    extern bool compare_algorithms_by_id(algorithm* one, algorithm* two);
}

#endif
