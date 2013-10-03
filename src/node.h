#ifndef NODE_H
#define NODE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "helpers.h"
#include "param.h"
#include "random.h"

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
			  params(0), minimum((-1) * std::numeric_limits<float>::infinity()), maximum(std::numeric_limits<float>::infinity()),
			  minimum_true((-1) * std::numeric_limits<float>::infinity()), maximum_true(std::numeric_limits<float>::infinity()),
			  traced(false), render_info_set(false), mutated_params_updated(false)
		{
		}
		virtual ~node() {
			// if we prepared this subtree for rendering...
			if (render_info_set) {
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
		// subclasses: call this at the end of your implementation
		virtual void ephemeral_random(random* rng) {
			for (unsigned i = 0; i < params.size(); i++) {
				params[i]->ephemeral_random(rng);
			}
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->ephemeral_random(rng);
			}
		}

		// subclasses: call this at end of your implementation
		virtual void set_render_info(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
			// make sure this is not primitive
			assert(!is_primitive());

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
				descendants[i]->set_render_info(sample_rate, block_size, max_frame_number, max_frame_start_time);
			}

			render_info_set = true;
		}

		// subclasses: call this at the end of your implementation
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
				mutated_params_updated = false;
			}
		}

		// subclasses: call this at the beginning of your implementation
		virtual void update_mutated_params() {
			assert(render_info_set == true);
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->update_mutated_params();
			}
			mutated_params_updated = true;
		}

		// true if any of its params or descendants have null values
		// subclasses: call this anded with your return value
		virtual bool is_primitive() {
			bool is_primitive = false;
			for (unsigned i = 0; i < arity; i++) {
				is_primitive = is_primitive || descendants[i] == NULL || descendants[i]->is_primitive();
			}
			for (unsigned i = 0; i < params.size(); i++) {
				is_primitive = is_primitive || params[i] == NULL || params[i]->is_uninstantiated();
			}
			return is_primitive;
		}

		// methods that won't be implemented in subclasses
		// true if this node is ready to render
		bool is_ready_to_render() {
			return render_info_set && mutated_params_updated;
		}

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

			// set traced as true
			traced = true;
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

	protected:
		std::string symbol;
		bool traced;
		bool render_info_set;
		bool mutated_params_updated;

	private:
	};
}


#endif
