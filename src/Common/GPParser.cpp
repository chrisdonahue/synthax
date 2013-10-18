#include "GPParser.h"

/*
    =========
    TOKENIZER
    =========
*/

// http://stackoverflow.com/a/236803
std::vector<std::string> &split(const std::string &s, std::vector<std::string> &elems, const char* delims) {
    std::size_t prev = 0, pos;
    while ((pos = s.find_first_of(delims, prev)) != std::string::npos)
    {
        if (pos > prev)
            elems.push_back(s.substr(prev, pos-prev));
        prev = pos+1;
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, const char* delims) {
    std::vector<std::string> elems;
    split(s, elems, delims);
    return elems;
}

/*
    ====================
    S-EXPRESSION PARSING
    ====================
*/

std::vector<GPMutatableParam*> parseMutatableParams(tokenizerFunctionArgs) {
    std::vector<GPMutatableParam*> ret;
    unsigned tokens_remaining = tokens.size() - (*currentIndex);
    GPMutatableParam* current = NULL;

    // if we have at least 4 tokens remaining
    while (tokens_remaining >= 4) {
        // try to make a mutatable param
        current = createMutatableParam(tokenizerArgs, "", true);

        // if bad parse reset the tokenizer position and break
        if (current == NULL) {
            *currentIndex -= 4;
            break;
        }

        // otherwise add it to the return array
        else {
            ret.push_back(current);
        }
        
        // update number of tokens remaining
        tokens_remaining = tokens.size() - (*currentIndex);
    }

    // return the list of mutatable params
    return ret;
}

GPMutatableParam* createMutatableParam(tokenizerFunctionArgs, std::string type, bool ismutatable) {
	// make sure we're not out of tokens
    unsigned tokens_remaining = tokens.size() - (*currentIndex);
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
        return new GPMutatableParam(type, ismutatable, val, min, max);
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
        return new GPMutatableParam(type, ismutatable, val, min, max);
    }
    // else this isn't a mutatable param
    else {
        return NULL;
    }
}

/*
	returns true for a successful parse, false for an unsuccessful parse
*/

void parseChild(tokenizerFunctionArgs, GPNode** child) {
	// make sure we're not out of tokens
    unsigned tokens_remaining = tokens.size() - (*currentIndex);
	if (tokens_remaining <= 0) {
		throw std::runtime_error("no node found where one was expected");
	}

	// cache the type of the upcoming child to check later if it was intentionally null
	std::string child_type = tokens[*currentIndex];

	// create the child and deref the return value
	*child = createNode(tokenizerArgs);
	
	// check if return child null and return successful parse if it was intentional
	if (*child == NULL) {
		if (child_type.compare("null") != 0) {
			throw std::runtime_error("implementation error WTF...");
		}
	}
}

GPNode* createNode(tokenizerFunctionArgs) {
    // check to make sure we have a type token
    unsigned tokens_remaining = tokens.size() - (*currentIndex);
    if (tokens_remaining <= 0) {
        throw std::runtime_error("no node found where one was expected");
    }

    // parse node string tag
    std::string type = tokens[consume];

    // parse mutatable params list
    std::vector<GPMutatableParam*> params = parseMutatableParams(tokenizerArgs);

    // ADSR nodes
    if (type.compare("adsr") == 0) {
        if (params.size() != 7) {
			throw std::runtime_error("incorrect number of mutatable params for adsr");
        }
        params[0]->setType("adsr_terminal_delay");
        params[1]->setType("adsr_terminal_attack");
        params[2]->setType("adsr_terminal_attack_height");
        params[3]->setType("adsr_terminal_decay");
        params[4]->setType("adsr_terminal_sustain");
        params[5]->setType("adsr_terminal_sustain_height");
        params[6]->setType("adsr_terminal_release");

        return new ADSRTerminalNode(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
    }
    else if (type.compare("adsr*") == 0) {
        if (params.size() != 7) {
			throw std::runtime_error("incorrect number of mutatable params for adsr*");
        }
        params[0]->setType("adsr_envelope_delay");
        params[1]->setType("adsr_envelope_attack");
        params[2]->setType("adsr_envelope_attack_height");
        params[3]->setType("adsr_envelope_decay");
        params[4]->setType("adsr_envelope_sustain");
        params[5]->setType("adsr_envelope_sustain_height");
        params[6]->setType("adsr_envelope_release");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new ADSREnvelopeNode(params[0], params[1], params[2], params[3], params[4], params[5], params[6], signal);
    }
    // constant nodes
    else if (type.compare("pi") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for pi");
        }

        return new ConstantNode(true, NULL);
    }
    else if (type.compare("const") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for const");
        }
        params[0]->setType("constant_value");

        return new ConstantNode(false, params[0]);
    }
    else if (type.compare("gain") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for gain");
        }
        params[0]->setType("gain_value");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new GainNode(params[0], signal);
    }
    // function nodes
    else if (type.compare("+") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for +");
        }

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
        
		GPNode* signalone;
		parseChild(tokenizerArgs, &signalone);

        return new AddNode(signalzero, signalone);
    }
    else if (type.compare("-") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for -");
        }

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
        
		GPNode* signalone;
		parseChild(tokenizerArgs, &signalone);

        return new SubtractNode(signalzero, signalone);
    }
    else if (type.compare("*") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for *"); 
        }

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
        
		GPNode* signalone;
		parseChild(tokenizerArgs, &signalone);

        return new MultiplyNode(signalzero, signalone);
    }
    else if (type.compare("sin") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for sin");
        }

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
       
        return new SineNode(signalzero);
    }
    else if (type.compare("cos") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for cos");
        }

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
       
        return new CosineNode(signalzero);
    }
    // LFO nodes
    else if (type.compare("lfo") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for lfo");
        }
        params[0]->setType("lfo_terminal_rate");

        return new LFOTerminalNode(params[0]);
    }
    else if (type.compare("lfo*") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for lfo*");
        }
        params[0]->setType("lfo_envelope_rate");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new LFOEnvelopeNode(params[0], signal);
    }
    // mixer nodes
    else if (type.compare("switch") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for switch");
        }

		GPNode* control;
		parseChild(tokenizerArgs, &control);

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
        
		GPNode* signalone;
		parseChild(tokenizerArgs, &signalone);

        return new SwitchNode(control, signalzero, signalone);
    }
    else if (type.compare("mix") == 0) {
        if (params.size() != 0) {
			throw std::runtime_error("incorrect number of mutatable params for mix");
        }

		GPNode* control;
		parseChild(tokenizerArgs, &control);

		GPNode* signalzero;
		parseChild(tokenizerArgs, &signalzero);
        
		GPNode* signalone;
		parseChild(tokenizerArgs, &signalone);

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
        params[0]->setType("am_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("am_partial");
        params[2]->setType("am_offset");
        params[3]->setType("am_alpha");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new AMNode(params[0], params[1], params[2], params[3], signal);
    }
    else if (type.compare("pm") == 0) {
        if (params.size() != 3) {
			throw std::runtime_error("incorrect number of mutatable params for pm");
        }
        params[0]->setType("pm_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("pm_partial");
        params[2]->setType("pm_index");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new PMNode(params[0], params[1], params[2], signal);
    }
    else if (type.compare("fm") == 0) {
        if (params.size() != 5) {
			throw std::runtime_error("incorrect number of mutatable params for fm");
        }
        params[0]->setType("fm_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("fm_partial");
        params[2]->setType("fm_mf_low");
        params[3]->setType("fm_mf_high");
        params[4]->setType("fm_index");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new FMNode(params[0], params[1], params[2], params[3], params[4], signal);
    }
    // wave table freq nodes
    else if (type.compare("sinfreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for sinfreqosc");
        }
        params[0]->setType("sinfreqosc_phase");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new SinFreqOscNode(params[0], signal);
    }
    else if (type.compare("sawfreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for sawfreqosc");
        }
        params[0]->setType("sawfreqosc_phase");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new SawFreqOscNode(params[0], signal);
    }
    else if (type.compare("squarefreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for squarefrecosc");
        }
        params[0]->setType("squarefreqosc_phase");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

        return new SquareFreqOscNode(params[0], signal);
    }
    else if (type.compare("trianglefreqosc") == 0) {
        if (params.size() != 1) {
			throw std::runtime_error("incorrect number of mutatable params for trianglefreqosc");
        }
        params[0]->setType("trianglefreqosc_phase");

		GPNode* signal;
		parseChild(tokenizerArgs, &signal);

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
            params[0]->setType("spline_type");
            params[0]->setUnmutatable();
            params[1]->setType("spline_num_points");
            params[2]->setType("spline_amp_range");
            params[3]->setType("spline_segment_length_range");

            std::vector<GPMutatableParam*>* splinepoints = new std::vector<GPMutatableParam*>();
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
            params[0]->setType("spline_type");
            params[0]->setUnmutatable();
            params[1]->setType("spline_num_points");
            params[1]->setUnmutatable();

            std::vector<GPMutatableParam*>* splinepoints = new std::vector<GPMutatableParam*>();
            unsigned currentParam = 2;
            while (currentParam + 2 < params.size()) {
                params[currentParam]->setType("spline_amp");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
                params[currentParam]->setType("spline_segment_length");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
            }
            params[currentParam]->setType("spline_amp_final");
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
            params[0]->setType("spline_type");
            params[0]->setUnmutatable();
            params[1]->setType("spline_num_points");
            params[2]->setType("spline_amp_range");
            params[3]->setType("spline_segment_length_range");

            std::vector<GPMutatableParam*>* splinepoints = new std::vector<GPMutatableParam*>();
            splinepoints->push_back(params[2]);
            splinepoints->push_back(params[3]);

            GPNode* signal;
            parseChild(tokenizerArgs, &signal);

            return new SplineEnvelopeNode(params[0], params[1], splinepoints, signal);
        }
        // else interpret this is a previously instantiated spline
        else {
            // make sure we at least have a type, numPoints and final length
            if (params.size() < 3) {
				throw std::runtime_error("incorrect number of mutatable params for spline*");
            }
            params[0]->setType("spline_type");
            params[0]->setUnmutatable();
            params[1]->setType("spline_num_points");
            params[1]->setUnmutatable();

            std::vector<GPMutatableParam*>* splinepoints = new std::vector<GPMutatableParam*>();
            unsigned currentParam = 2;
            while (currentParam + 2 < params.size()) {
                params[currentParam]->setType("spline_amp");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
                params[currentParam]->setType("spline_segment_length");
                splinepoints->push_back(params[currentParam]);
                currentParam++;
            }
            params[currentParam]->setType("spline_amp_final");
            splinepoints->push_back(params[currentParam]);

            GPNode* signal;
            parseChild(tokenizerArgs, &signal);

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
        params[0]->setType("var_num");
        params[0]->setUnmutatable();
        params[1]->setType("var_range");
        params[1]->setUnmutatable();

        return new VariableNode(params[0], params[1]);
    }
    // wave table oscillator nodes
    else if (type.compare("sinosc") == 0) {
        if (params.size() != 3) {
            throw std::runtime_error("incorrect number of mutatable params for sinosc");
        }
        params[0]->setType("sinosc_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("sinosc_partial");
        params[2]->setType("sinosc_phase");

        return new SinOscNode(params[0], params[1], params[2]);
    }
    else if (type.compare("sawosc") == 0) {
        if (params.size() != 3) {
            throw std::runtime_error("incorrect number of mutatable params for sawosc");
        }
        params[0]->setType("sawosc_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("sawosc_partial");
        params[2]->setType("sawosc_phase");

        return new SawOscNode(params[0], params[1], params[2]);
    }
    else if (type.compare("squareosc") == 0) {
        if (params.size() != 3) {
            throw std::runtime_error("incorrect number of mutatable params for squareosc");
        }
        params[0]->setType("squareosc_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("squareosc_partial");
        params[2]->setType("squareosc_phase");

        return new SquareOscNode(params[0], params[1], params[2]);
    }
    else if (type.compare("triangleosc") == 0) {
        if (params.size() != 3) {
			throw std::runtime_error("incorrect number of mutatable params for triangleosc");
        }
        params[0]->setType("triangleosc_var_num");
        params[0]->setUnmutatable();
        params[1]->setType("triangleosc_partial");
        params[2]->setType("triangleosc_phase");

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

GPNode* createNode(const std::string node_string, std::string* error_string) {
    // init return values
	GPNode* ret = NULL;
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
		ret = createNode(tokens, &index);
	}
	catch (std::runtime_error e) {
		*error_string = e.what();
	}
	return ret;
}

GPMutatableParam* createMutatableParam(std::string param_string, std::string type, bool ismutatable, std::string* error_string) {
    // init return values
	GPMutatableParam* ret = NULL;
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
		ret = createMutatableParam(tokens, &index, type, ismutatable);
	}
	catch (std::runtime_error e) {
		*error_string = e.what();
	}
	return ret;
}
