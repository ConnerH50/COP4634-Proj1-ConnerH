#include "parse.hpp"


int main(int argc, char**argv){

	Parser parse;
	string input;
	bool inDebug = false;

	if(argv[1] != NULL && string(argv[1]) == "-Debug"){
		inDebug = true;
	}

			

	do{
		parse.runParser(inDebug);
		input = parse.getUserString();
		parse.freeMem(); // free the memory allocated in runParser

	} while(input != "exit\n"); 

	

	return 0;
}
