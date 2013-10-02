#ifndef NODE_H
#define NODE_H

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

		// PURE VIRTUAL METHODS THAT ALL SUBCLASSES WILL IMPLEMENT
		// might want this to be a collection of nodes returned
		// virtual node* getPrimitive() = 0;
		// virtual node* fromString(std::string nodestring) = 0;
		virtual node* getCopy() = 0;
		virtual void evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) = 0;

		// LINEAGE POINTERS
		node* parent;
		std::vector<node*> descendants;
		std::vector<float*> descendant_buffers;

		// TREE STATE
		int depth;
		unsigned arity;

		// MUTATABLE PARAM RELATED
		std::vector<param*> params;
		float minimum;
		float maximum;
		float minimum_true;
		float maximum_true;

		// READY TO RENDER
		bool render_info_set;
		bool prepared_to_render;

		// OVERRIDABLE FUNCTIONS
		virtual void ephemeralRandom(random* rng) {
			for (unsigned i = 0; i < params.size(); i++) {
				params[i]->ephemeralRandom(rng);
			}
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->ephemeralRandom(rng);
			}
		}

		virtual void prepareToPlay() {
		}

		virtual void setRenderInfo(float sr, unsigned blockSize, unsigned maxFrameNumber, float maxTime) {
			// clear out old render info if it exists
			doneRendering();

			// allocate some new buffers in case blockSize changed
			unsigned numdescendant_buffers = arity == 0 ? 0 : arity - 1;
			descendant_buffers.resize(numdescendant_buffers, NULL);
			for (unsigned i = 0; i < numdescendant_buffers; i++) {
				descendant_buffers[i] = (float*) malloc(sizeof(float) * blockSize);
			}

			// recursively execute
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->setRenderInfo(sr, blockSize, maxFrameNumber, maxTime);
			}

			render_info_set = true;
		}

		virtual void doneRendering() {
			if (render_info_set) {
				unsigned numdescendant_buffers = arity == 0 ? 0 : arity - 1;
				for (unsigned i = 0; i < numdescendant_buffers; i++) {
					free(descendant_buffers[i]);
				}

				for (unsigned i = 0; i < arity; i++) {
					descendants[i]->doneRendering();
				}
            
				render_info_set = false;
				prepared_to_render = false;
			}
		}

		virtual void updateMutatedParams() {
			assert(render_info_set == true);
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->updateMutatedParams();
			}
			prepared_to_render = true;
		}

		// NON-OVERRIDABLE FUNCTIONS
		// this trace method ensures that I only have assign descendant pointers correctly during genetic operations
		void trace(std::vector<node*>* allnodes, std::vector<param*>* allparams, node* p, int* treeHeight, int currentDepth) {
			// assign parent
			parent = p;

			// assign depth
			depth = currentDepth;

			// add this node to the collection of all nodes
			allnodes->push_back(this);
        
			// add this nodes mutatable params to the collection of all mutatable params
			for (unsigned i = 0; i < params.size(); i++) {
				if (params[i]->isMutatable())
					allparams->push_back(params[i]);
			}
        
			// update tree height if necessary
			if (currentDepth > *treeHeight) {
				*treeHeight = currentDepth;
			}

			// trace the rest of the tree
			for (unsigned i = 0; i < arity; i++) {
				descendants[i]->trace(allnodes, allparams, this, treeHeight, currentDepth + 1);
			}
		};

		std::string toString(unsigned precision) {
			std::stringstream ss;
			ss.precision(precision);
			toString(ss);
			return ss.str();
		}

		void toString(std::stringstream& ss) {
			ss << "(" << symbol;
			for (unsigned i = 0; i < params.size(); i++) {
				ss << " ";
				params[i]->toString(ss);
			}
			for (unsigned i = 0; i < descendants.size(); i++) {
				node* descendant = descendants[i];
				// TODO: change to check for primitive
				ss << " ";
				if (descendant != NULL) {
					descendants[i]->toString(ss);
				}
				else {
					ss << "(null)";
				}
			}
			ss << ")";
		}

	protected:
		std::string symbol;
	};
}


#endif
