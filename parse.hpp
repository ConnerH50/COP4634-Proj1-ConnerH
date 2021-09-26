#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/wait.h>

using namespace std;

#define MAXARGS 32 

class Parser{

	private:
		char *inputRedirect;
		char *outputRedirect;
		int background, argumentCount;
		char **argumentVector;
		char *userString;

	public:
		Parser();
		void runParser(bool inDebug);
		void setArgumentCount(int argumentCount);
		int getArgumentCount();
		int getBackground();
		char *getInputRedirect();
		char *getOutputRedirect();
		char *getUserInput();
		char *getUserString();
		char **getArgumentVector();
		char *getVectorIndex(int index);
		char **parseInput(char *userString);
		void printParams();
		void freeMem();


};
#endif
