#include "parse.hpp"

void runShell(Parser parse){

}


int main(int argc, char**argv){

	Parser parse;
	string input;
	bool inDebug = false;

	if(argv[1] != NULL && string(argv[1]) == "-Debug"){
		inDebug = true;
	}

			

	/*do*/  while(input != "exit\n"){
		parse.runParser(inDebug);
		input = parse.getUserString();

		//char *cmd[] = {"ls", "-l", NULL};

		execvp("ls", parse.getArgumentVector());
		//execvp("ls", cmd);

		parse.freeMem(); // free the memory allocated in runParser

	} //while(input != "exit\n"); 

	

	return 0;
}
