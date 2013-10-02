#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "param.h"
#include "primitives.h"

#include <exception>
#include <string>
#include <sstream>
#include <vector>

namespace synthax {
	namespace parser {
		// tokenizer
		extern std::vector<std::string>& split(const std::string &s, std::vector<std::string> &elems, const char* delims);
		extern std::vector<std::string> split(const std::string &s, const char* delims);

		// parser
		// macro to "consume" a token when we observe it
		#define consume (*current_index)++
		#define tokenizer_function_args std::vector<std::string> tokens, unsigned* current_index
		#define tokenizer_args tokens, current_index
		extern std::vector<param*> parse_mutatable_params(tokenizer_function_args);
		extern param* create_mutatable_param(tokenizer_function_args, std::string type, bool ismutatable);
		extern void parse_child(tokenizer_function_args, node** child);
		extern node* create_node(tokenizer_function_args);

		// accesors
		extern node* create_node(const std::string node_string, std::string* error_string);
		extern param* create_mutatable_param(std::string param_string, std::string type, bool is_mutatable, std::string* error_string);
	}
}

#endif