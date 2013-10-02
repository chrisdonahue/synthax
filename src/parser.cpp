#include "parser.h"

/*
    =========
    tokenizer
    =========
*/

// http://stackoverflow.com/a/236803
std::vector<std::string>& synthax::parser::split(const std::string &s, std::vector<std::string> &elems, const char* delims) {
    std::size_t prev = 0, pos;
    while ((pos = s.find_first_of(delims, prev)) != std::string::npos)
    {
        if (pos > prev)
            elems.push_back(s.substr(prev, pos-prev));
        prev = pos+1;
    }
    return elems;
}

std::vector<std::string> synthax::parser::split(const std::string &s, const char* delims) {
    std::vector<std::string> elems;
    split(s, elems, delims);
    return elems;
}

/*
    ======
    parser
    ======
*/

std::vector<param*> synthax::parser::parse_mutatable_params(tokenizer_function_args) {
    std::vector<param*> ret;
    unsigned tokens_remaining = tokens.size() - (*current_index);
    param* current = NULL;

    // if we have at least 4 tokens remaining
    while (tokens_remaining >= 4) {
        // try to make a mutatable param
        current = create_mutatable_param(tokenizer_args, "", true);

        // if bad parse reset the tokenizer position and break
        if (current == NULL) {
            *current_index -= 4;
            break;
        }

        // otherwise add it to the return array
        else {
            ret.push_back(current);
        }
        
        // update number of tokens remaining
        tokens_remaining = tokens.size() - (*current_index);
    }

    // return the list of mutatable params
    return ret;
}

param* synthax::parser::create_mutatable_param(tokenizer_function_args, std::string type, bool ismutatable) {
	// make sure we're not out of tokens
    unsigned tokens_remaining = tokens.size() - (*current_index);
	if (tokens_remaining < 4) {
		throw std::runtime_error("not enough tokens to create mutatable param");
	}

    // get tokens
    std::string tag = tokens[consume];
    std::string minstr = tokens[consume];
    std::string valstr = tokens[consume];
    std::string maxstr = tokens[consume];

    // if the param is continuous
    if (tag.compare("c") == 0) {
        float min = (float) std::atof(minstr.c_str());
        float val = (float) std::atof(valstr.c_str());
        float max = (float) std::atof(maxstr.c_str());
        if (min > val || val > max || min > max) {
			std::stringstream ss;
            ss << "invalid mutatable param: " << "{" << tag << " " << minstr << " " << valstr << " " << maxstr << "}";
			throw std::runtime_error(ss.str().c_str());
        }
        return new param(type, ismutatable, val, min, max);
    }
    // else if the param is discrete
    else if (tag.compare("d") == 0) {
        int min = std::atoi(minstr.c_str());
        int val = std::atoi(valstr.c_str());
        int max = std::atoi(maxstr.c_str());
        if (min > val || val > max || min > max) {
			std::stringstream ss;
            ss << "invalid mutatable param: " << "{" << tag << " " << minstr << " " << valstr << " " << maxstr << "}";
			throw std::runtime_error(ss.str().c_str());
        }
        return new param(type, ismutatable, val, min, max);
    }
    // else this isn't a mutatable param
    else {
        return NULL;
    }
}

/*
	returns true for a successful parse, false for an unsuccessful parse
*/

void synthax::parser::parse_child(tokenizer_function_args, node** child) {
	// make sure we're not out of tokens
    unsigned tokens_remaining = tokens.size() - (*current_index);
	if (tokens_remaining <= 0) {
		throw std::runtime_error("no node found where one was expected");
	}

	// cache the type of the upcoming child to check later if it was intentionally null
	std::string child_type = tokens[*current_index];

	// create the child and deref the return value
	*child = create_node(tokenizer_args);
	
	// check if return child null and return successful parse if it was intentional
	if (*child == NULL) {
		if (child_type.compare("null") != 0) {
			throw std::runtime_error("implementation error WTF...");
		}
	}
}

node* synthax::parser::create_node(tokenizer_function_args) {
    // check to make sure we have a type token
    unsigned tokens_remaining = tokens.size() - (*current_index);
    if (tokens_remaining <= 0) {
        throw std::runtime_error("no node found where one was expected");
    }

    // parse node string tag
    std::string type = tokens[consume];

    // parse mutatable params list
    std::vector<param*> params = parse_mutatable_params(tokenizer_args);

    // ADSR nodes
    if (type.compare("adsr") == 0) {
        if (params.size() != 7) {
			throw std::runtime_error("incorrect number of mutatable params for adsr");
        }
        params[0]->set_type("adsr_terminal_delay");
        params[1]->set_type("adsr_terminal_attack");
        params[2]->set_type("adsr_terminal_attack_height");
        params[3]->set_type("adsr_terminal_decay");
        params[4]->set_type("adsr_terminal_sustain");
        params[5]->set_type("adsr_terminal_sustain_height");
        params[6]->set_type("adsr_terminal_release");

        return new synthax::primitive::terminal::adsr(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
    }
    else if (type.compare("adsr*") == 0) {
        if (params.size() != 7) {
			throw std::runtime_error("incorrect number of mutatable params for adsr*");
        }
        params[0]->set_type("adsr_envelope_delay");
        params[1]->set_type("adsr_envelope_attack");
        params[2]->set_type("adsr_envelope_attack_height");
        params[3]->set_type("adsr_envelope_decay");
        params[4]->set_type("adsr_envelope_sustain");
        params[5]->set_type("adsr_envelope_sustain_height");
        params[6]->set_type("adsr_envelope_release");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new synthax::primitive::envelope::adsr(params[0], params[1], params[2], params[3], params[4], params[5], params[6], signal);
    }
    // constant nodes
    else if (type.compare("pi") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for pi");
        }

        return new synthax::primitive::terminal::constant(true, NULL);
    }
    else if (type.compare("const") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for const");
        }
        params[0]->set_type("constant_value");

        return new synthax::primitive::terminal::constant(false, params[0]);
    }
    else if (type.compare("gain") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for gain");
        }
        params[0]->set_type("gain_value");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new synthax::primitive::envelope::gain(params[0], signal);
    }
    // function nodes
    else if (type.compare("+") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for +");
        }

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
        
		node* signalone;
		parse_child(tokenizer_args, &signalone);

        return new AddNode(signalzero, signalone);
    }
    else if (type.compare("-") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for -");
        }

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
        
		node* signalone;
		parse_child(tokenizer_args, &signalone);

        return new SubtractNode(signalzero, signalone);
    }
    else if (type.compare("*") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for *"); 
        }

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
        
		node* signalone;
		parse_child(tokenizer_args, &signalone);

        return new MultiplyNode(signalzero, signalone);
    }
    else if (type.compare("sin") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for sin");
        }

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
       
        return new SineNode(signalzero);
    }
    else if (type.compare("cos") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for cos");
        }

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
       
        return new CosineNode(signalzero);
    }
    // LFO nodes
    else if (type.compare("lfo") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for lfo");
        }
        params[0]->set_type("lfo_terminal_rate");

        return new LFOTerminalNode(params[0]);
    }
    else if (type.compare("lfo*") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for lfo*");
        }
        params[0]->set_type("lfo_envelope_rate");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new LFOEnvelopeNode(params[0], signal);
    }
    // mixer nodes
    else if (type.compare("switch") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for switch");
        }

		node* control;
		parse_child(tokenizer_args, &control);

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
        
		node* signalone;
		parse_child(tokenizer_args, &signalone);

        return new SwitchNode(control, signalzero, signalone);
    }
    else if (type.compare("mix") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for mix");
        }

		node* control;
		parse_child(tokenizer_args, &control);

		node* signalzero;
		parse_child(tokenizer_args, &signalzero);
        
		node* signalone;
		parse_child(tokenizer_args, &signalone);

        return new MixerNode(control, signalzero, signalone);
    }
    // noise node
    else if (type.compare("whitenoise") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for whitenoise");
        }

        return new NoiseNode();
    }
    // modulation nodes
    else if (type.compare("am") == 0) {
        if (params.size() != 4) {
			throw std::runtime_error("incorrect number of mutatable params for am");
        }
        params[0]->set_type("am_var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("am_partial");
        params[2]->set_type("am_offset");
        params[3]->set_type("am_alpha");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new AMNode(params[0], params[1], params[2], params[3], signal);
    }
    else if (type.compare("pm") == 0) {
        if (params.size() != 3) {
			throw std::runtime_error("incorrect number of mutatable params for pm");
        }
        params[0]->set_type("pm_var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("pm_partial");
        params[2]->set_type("pm_index");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new PMNode(params[0], params[1], params[2], signal);
    }
    // wave table freq nodes
    else if (type.compare("sinfreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for sinfreqosc");
        }
        params[0]->set_type("sinfreqosc_phase");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new SinFreqOscNode(params[0], signal);
    }
    else if (type.compare("sawfreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for sawfreqosc");
        }
        params[0]->set_type("sawfreqosc_phase");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new SawFreqOscNode(params[0], signal);
    }
    else if (type.compare("squarefreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for squarefrecosc");
        }
        params[0]->set_type("squarefreqosc_phase");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new SquareFreqOscNode(params[0], signal);
    }
    else if (type.compare("trianglefreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for trianglefreqosc");
        }
        params[0]->set_type("trianglefreqosc_phase");

		node* signal;
		parse_child(tokenizer_args, &signal);

        return new TriangleFreqOscNode(params[0], signal);
    }
    // silence node
    else if (type.compare("silence") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for silence");
        }

        return new SilenceNode();
    }
    // spline node (already created)
    else if (type.compare("spline") == 0) {
        // if this is a primitive spline that we want to randomize
        if (params.size() % 2 == 0) {
            // make sure we have the right number of arguments
            if (params.size() != 4) {
				throw std::runtime_error("incorrect number of mutatable params for spline primitive");
            }
            params[0]->set_type("spline_type");
            params[0]->set_unmutatable();
            params[1]->set_type("spline_num_points");
            params[2]->set_type("spline_amp_range");
            params[3]->set_type("spline_segment_length_range");

            std::vector<param*>* splinepoints = new std::vector<param*>();
            splinepoints->push_back(params[2]);
            splinepoints->push_back(params[3]);

            return new SplineTerminalNode(params[0], params[1], splinepoints);
        }
        // else interpret this is a previously instantiated spline
        else {
            // make sure we at least have a type, numPoints and final length
            if (params.size() < 3) {
				throw std::runtime_error("incorrect number of mutatable params for spline");
            }
            params[0]->set_type("spline_type");
            params[0]->set_unmutatable();
            params[1]->set_type("spline_num_points");
            params[1]->set_unmutatable();

            std::vector<param*>* splinepoints = new std::vector<param*>();
            unsigned currentParam = 2;
            while (currentParam + 2 < params.size()) {
                params[currentParam]->set_type("spline_amp");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
                params[currentParam]->set_type("spline_segment_length");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
            }
            params[currentParam]->set_type("spline_amp_final");
            splinepoints->push_back(params[currentParam]);

            return new SplineTerminalNode(params[0], params[1], splinepoints);
        }
    }
    else if (type.compare("spline*") == 0) {
        // if this is a primitive spline that we want to randomize
        if (params.size() % 2 == 0) {
            // make sure we have the right number of arguments
            if (params.size() != 4) {
				throw std::runtime_error("incorrect number of mutatable params for spline* primitive");
            }
            params[0]->set_type("spline_type");
            params[0]->set_unmutatable();
            params[1]->set_type("spline_num_points");
            params[2]->set_type("spline_amp_range");
            params[3]->set_type("spline_segment_length_range");

            std::vector<param*>* splinepoints = new std::vector<param*>();
            splinepoints->push_back(params[2]);
            splinepoints->push_back(params[3]);

            node* signal;
            parse_child(tokenizer_args, &signal);

            return new SplineEnvelopeNode(params[0], params[1], splinepoints, signal);
        }
        // else interpret this is a previously instantiated spline
        else {
            // make sure we at least have a type, numPoints and final length
            if (params.size() < 3) {
				throw std::runtime_error("incorrect number of mutatable params for spline*");
            }
            params[0]->set_type("spline_type");
            params[0]->set_unmutatable();
            params[1]->set_type("spline_num_points");
            params[1]->set_unmutatable();

            std::vector<param*>* splinepoints = new std::vector<param*>();
            unsigned currentParam = 2;
            while (currentParam + 2 < params.size()) {
                params[currentParam]->set_type("spline_amp");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
                params[currentParam]->set_type("spline_segment_length");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
            }
            params[currentParam]->set_type("spline_amp_final");
            splinepoints->push_back(params[currentParam]);

            node* signal;
            parse_child(tokenizer_args, &signal);

            return new SplineEnvelopeNode(params[0], params[1], splinepoints, signal);
        }
    }
    // time node
    else if (type.compare("time") == 0) {
        if (params.size() != 0) {
            throw std::runtime_error("incorrect number of mutatable params for time");
        }

        return new TimeNode();
    }
    // variable node
    else if (type.compare("var") == 0) {
        if (params.size() != 2) {
            throw std::runtime_error("incorrect number of mutatable params for var");
        }
        params[0]->set_type("var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("var_range");
        params[1]->set_unmutatable();

        return new VariableNode(params[0], params[1]);
    }
    // wave table oscillator nodes
    else if (type.compare("sinosc") == 0) {
        if (params.size() != 3) {
            throw std::runtime_error("incorrect number of mutatable params for sinosc");
        }
        params[0]->set_type("sinosc_var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("sinosc_partial");
        params[2]->set_type("sinosc_phase");

        return new SinOscNode(params[0], params[1], params[2]);
    }
    else if (type.compare("sawosc") == 0) {
        if (params.size() != 3) {
            throw std::runtime_error("incorrect number of mutatable params for sawosc");
        }
        params[0]->set_type("sawosc_var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("sawosc_partial");
        params[2]->set_type("sawosc_phase");

        return new SawOscNode(params[0], params[1], params[2]);
    }
    else if (type.compare("squareosc") == 0) {
        if (params.size() != 3) {
            throw std::runtime_error("incorrect number of mutatable params for squareosc");
        }
        params[0]->set_type("squareosc_var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("squareosc_partial");
        params[2]->set_type("squareosc_phase");

        return new SquareOscNode(params[0], params[1], params[2]);
    }
    else if (type.compare("triangleosc") == 0) {
        if (params.size() != 3) {
			throw std::runtime_error("incorrect number of mutatable params for triangleosc");
        }
        params[0]->set_type("triangleosc_var_num");
        params[0]->set_unmutatable();
        params[1]->set_type("triangleosc_partial");
        params[2]->set_type("triangleosc_phase");

        return new TriangleOscNode(params[0], params[1], params[2]);
    }
	// explicitly null node for primitives
	else if (type.compare("null") == 0) {
		return NULL;
	}
	// otherwise node type string is invalid
    else {
		std::stringstream ss;
		ss << "invalid node type: " << type;
		throw std::runtime_error(ss.str().c_str());
    }
}

/*
    ===========
    EASY ACCESS
    ===========
*/

node* synthax::parser::create_node(const std::string node_string, std::string* error_string) {
    // init return values
	node* ret = NULL;
	*error_string = "";

    // split input into tokens
	std::vector<std::string> tokens = split(node_string, " }{)(");
    unsigned index = 0;
    if (tokens.size() == 0) {
        *error_string = "input string improperly formatted";
        return ret;
    }

    // try to create a node, catching runtime errors 
	try {
		ret = create_node(tokens, &index);
	}
	catch (std::runtime_error e) {
		*error_string = e.what();
	}
	return ret;
}

param* synthax::parser::create_mutatable_param(std::string param_string, std::string type, bool ismutatable, std::string* error_string) {
    // init return values
	param* ret = NULL;
	*error_string = "";

	// split input into tokens
	std::vector<std::string> tokens = split(param_string, " }{)(");
    unsigned index = 0;
    if (tokens.size() == 0) {
        *error_string = "input string improperly formatted";
        return ret;
    }

    // try to create a node, catching runtime errors 
	try {
		ret = create_mutatable_param(tokens, &index, type, ismutatable);
	}
	catch (std::runtime_error e) {
		*error_string = e.what();
	}
	return ret;
}