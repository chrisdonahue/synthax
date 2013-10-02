#ifndef NODE_H
#define NODE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../common/helpers.h"
#include "../common/random.h"
#include "param.h"

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
#include <vector>

namespace synthax {
	class node {
	public:
        // constructors
		node()
			: parent(NULL), descendants(0), descendant_buffers(0),
			  depth(-1),
			  params(0), minimum((-1) * std::numeric_limits<float>::infinity()), maximum(std::numeric_limits<float>::infinity()), minimum_true((-1) * std::numeric_limits<float>::infinity()), maximum_true(std::numeric_limits<float>::infinity()),
			  render_info_set(false), prepared_to_render(false)
		{
		}
		virtual ~node() {
			// if we prepared this subtree for rendering...
			if (prepared_to_render) {
				unsigned numdescendant_buffers = arity == 0 ? 0 : arity - 1;
				for (unsigned i = 0; i < numdescendant_buffers; i++) {
					free(descendant_buffers[i]);
				}
			}
			for (unsigned i = 0; i < arity; i++) {
				delete descendants[i];
			}
			for (unsigned i = 0; i < params.size(); i++) {
				delete params[i];
			}
		}

		// pure virtual methods required to be implemented in subclasses
		virtual node* get_copy() = 0;
		virtual void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) = 0;

		// virtual methods optionally implemented in subclasses
		virtual void ephemeral_random(random* rng) {
			for (unsigned i = 0; i < params.size(); i++) {
				params[i]->ephemeral_random(rng);
			}
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->ephemeral_random(rng);
			}
		}

		virtual void prepare_to_play() {
		}

		virtual void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
			// clear out old render info if it exists
			done_rendering();

			// allocate some new buffers in case block_size changed
			unsigned numdescendant_buffers = arity == 0 ? 0 : arity - 1;
			descendant_buffers.resize(numdescendant_buffers, NULL);
			for (unsigned i = 0; i < numdescendant_buffers; i++) {
				descendant_buffers[i] = (float*) malloc(sizeof(float) * block_size);
			}

			// recursively execute
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
			}

			render_info_set = true;
		}

		virtual void done_rendering() {
			if (render_info_set) {
				unsigned numdescendant_buffers = arity == 0 ? 0 : arity - 1;
				for (unsigned i = 0; i < numdescendant_buffers; i++) {
					free(descendant_buffers[i]);
				}

				for (unsigned i = 0; i < arity; i++) {
					descendants[i]->done_rendering();
				}
            
				render_info_set = false;
				prepared_to_render = false;
			}
		}

		virtual void update_mutated_params() {
			assert(render_info_set == true);
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->update_mutated_params();
			}
			prepared_to_render = true;
		}

		// methods that won't be implemented in subclasses
		// this trace method ensures that I only have assign descendant pointers correctly during genetic operations
		void trace(std::vector<node*>* all_nodes, std::vector<param*>* all_params, node* p, int* tree_height, int current_depth) {
			// assign parent
			parent = p;

			// assign depth
			depth = current_depth;

			// add this node to the collection of all nodes
			all_nodes->push_back(this);
        
			// add this nodes mutatable params to the collection of all mutatable params
			for (unsigned i = 0; i < params.size(); i++) {
				if (params[i]->is_mutatable())
					all_params->push_back(params[i]);
			}
        
			// update tree height if necessary
			if (current_depth > *tree_height) {
				*tree_height = current_depth;
			}

			// trace the rest of the tree
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->trace(all_nodes, all_params, this, tree_height, current_depth + 1);
			}
		};

		std::string to_string(unsigned precision) {
			std::stringstream ss;
			ss.precision(precision);
			to_string(ss);
			return ss.str();
		}

		void to_string(std::stringstream& ss) {
			ss << "(" << symbol;
			for (unsigned i = 0; i < params.size(); i++) {
				ss << " ";
				params[i]->to_string(ss);
			}
			for (unsigned i = 0; i < descendants.size(); i++) {
				node* descendant = descendants[i];
				// TODO: change to check for primitive
				ss << " ";
				if (descendant != NULL) {
					descendants[i]->to_string(ss);
				}
				else {
					ss << "(null)";
				}
			}
			ss << ")";
		}

		// lineage
		node* parent;
		std::vector<node*> descendants;
		std::vector<float*> descendant_buffers;

		// tree state
		int depth;
		unsigned arity;

		// parameter-related
		std::vector<param*> params;
		float minimum;
		float maximum;
		float minimum_true;
		float maximum_true;

		// indicators
		bool render_info_set;
		bool prepared_to_render;

	protected:
		std::string symbol;
	};
}


#endif
