#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAXARGS 32

class Parser{

	private:
		char *inputRedirect;
		char *outputRedirect;
		int background, argumentCount;
		char *argVector[MAXARGS];
		char *tokens;
		char *userString;

	public:
		Parser();
		void runParser();
		char *getUserInput();
		char *getUserString();


};
#endif
