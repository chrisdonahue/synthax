#ifndef GPPARSER_H
#define GPPARSER_H

#include <exception>
#include <string>
#include <sstream>
#include <vector>
#include "../Synth/GPNode.h"
#include "../Synth/GPPrimitives.h"

// TOKENIZER
extern std::vector<std::string> &split(const std::string &s, std::vector<std::string> &elems, const char* delims);
extern std::vector<std::string> split(const std::string &s, const char* delims);

// S-EXPRESSION PARSING
// macro to "consume" a token when we observe it
#define consume (*currentIndex)++
#define tokenizerFunctionArgs std::vector<std::string> tokens, unsigned* currentIndex
#define tokenizerArgs tokens, currentIndex
extern std::vector<GPMutatableParam*> parseMutatableParams(tokenizerFunctionArgs);
extern GPMutatableParam* createMutatableParam(tokenizerFunctionArgs, std::string type, bool ismutatable);
extern void parseChild(tokenizerFunctionArgs, GPNode** child);
extern GPNode* createNode(tokenizerFunctionArgs);

// EASY ACCESS
extern GPNode* createNode(const std::string node_string, std::string* error_string);
extern GPMutatableParam* createMutatableParam(std::string paramstring, std::string type, bool ismutatable, std::string* error_string);

#endif
