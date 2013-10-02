#include "algorithm.h"

/*
    ============
    construction
    ============
*/

synthax::algorithm::algorithm(node* r, std::string o) :
    id(-1), origin(o), height(-1), fitness(-1),
    minimum((-1) * std::numeric_limits<float>::infinity()), maximum(std::numeric_limits<float>::infinity()),
    traced(false), prepared_to_render(false),
    render_root(new primitive::terminal::silence()), root(r), all_nodes(0), all_mutatable_params(0)
{
}

synthax::algorithm::~algorithm() {
    if (!prepared_to_render) {
        delete root;
    }
    delete render_root;
}

synthax::algorithm* synthax::algorithm::get_copy(std::string neworigin) {
    algorithm* copy = new algorithm(root->get_copy(), neworigin);
    return copy;
}

/*
    ===========
    examination
    ===========
*/

void synthax::algorithm::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    render_root->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
}


std::string synthax::algorithm::to_string(unsigned precision) {
    std::stringstream ss;
    ss.precision(precision);
    root->to_string(ss);
    return ss.str();
}

synthax::node* synthax::algorithm::get_root() {
    return root;
}

bool synthax::algorithm::equals(algorithm* other, unsigned precision) {
    return to_string(precision).compare(other->to_string(precision)) == 0;
}

synthax::node* synthax::algorithm::get_random_network_node(random* r) {
    assert(traced = true);
    return all_nodes[r->drandom(all_nodes.size())];
}

std::vector<synthax::param*>* synthax::algorithm::get_all_mutatable_params() {
    assert(traced = true);
    return &all_mutatable_params;
}

/*
    =======
    helpers
    =======
*/

void synthax::algorithm::trace() {
    all_nodes.clear();
    all_mutatable_params.clear();
    root->trace(&all_nodes, &all_mutatable_params, NULL, &height, 0);
    traced = true;
}

// render_root = silence and root = realroot whenever prepared_to_render is false
// render_root = realroot and root = realroot whenever prepared_to_render is true
void synthax::algorithm::prepare_to_render(float sample_rate, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    done_rendering();
    if (!prepared_to_render) {
        delete render_root;
    }
    root->set_render_info(sample_rate, block_size, max_frame_number, max_frame_start_time);
    render_root = root;
    prepared_to_render = true;
    update_mutated_params();
}

// only changed the params
void synthax::algorithm::update_mutated_params() {
    assert(prepared_to_render);
    root->update_mutated_params();
    minimum = root->minimum;
    maximum = root->maximum;
}

void synthax::algorithm::done_rendering() {
    if (prepared_to_render) {
        root->done_rendering();
        minimum = (-1) * std::numeric_limits<float>::infinity();
        maximum = std::numeric_limits<float>::infinity();
        render_root = new primitive::terminal::silence();
        prepared_to_render = false;
    }
}

/*
    this method replaces the subtree rooted at node old with node new's
*/
void synthax::algorithm::replace_subtree(node* old, node* nu) {
    // handle root case
    if (old == root) {
        root = nu;
    }
    else {
        // replace parent-child links
        bool replaced_link = false;
        for (unsigned i = 0; i < old->parent->arity; i++) {
            if (old->parent->descendants[i] == old) {
                old->parent->descendants[i] = nu;
                replaced_link = true;
            }
        }
        if (!replaced_link)
            std::cerr << "Bad parent-child links detected during subtree replacement." << std::endl;
    }
    /*
    // assign nu parent pointer
    nu->parent = old->parent;
    */

    traced = false;
}

void synthax::algorithm::ephemeral_random(random* r) {
    root->ephemeral_random(r);
}

// method to compare networks by identification
bool synthax::compare_algorithms_by_id(algorithm* one, algorithm* two) {
	return one->id < two->id;
}
