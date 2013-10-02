#ifndef GPPARSER_H
#define GPPARSER_H

#include <exception>
#include <string>
#include <sstream>
#include <vector>
#include "../Synth/node.h"
#include "../Synth/GPPrimitives.h"

// TOKENIZER
extern std::vector<std::string> &split(const std::string &s, std::vector<std::string> &elems, const char* delims);
extern std::vector<std::string> split(const std::string &s, const char* delims);

// S-EXPRESSION PARSING
// macro to "consume" a token when we observe it
#define consume (*currentIndex)++
#define tokenizerFunctionArgs std::vector<std::string> tokens, unsigned* currentIndex
#define tokenizerArgs tokens, currentIndex
extern std::vector<param*> parseMutatableParams(tokenizerFunctionArgs);
extern param* createMutatableParam(tokenizerFunctionArgs, std::string type, bool ismutatable);
extern void parseChild(tokenizerFunctionArgs, node** child);
extern node* createNode(tokenizerFunctionArgs);

// EASY ACCESS
extern node* createNode(const std::string node_string, std::string* error_string);
extern param* createMutatableParam(std::string paramstring, std::string type, bool ismutatable, std::string* error_string);

#endif
