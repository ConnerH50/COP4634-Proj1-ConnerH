#include "parse.hpp"

void runShell(Parser parse, char** argv){
	int forkresult;
	pid_t cpid;
	cout << "in runShell()" << endl;
	
	forkresult = fork();

	if(forkresult != 0){ // parent runs this code
		cpid = wait(NULL); // wait for child to finish
	}else{ // child executes

		//cout << strlen(parse.getVectorIndex(0)) << endl;
		execvp(parse.getVectorIndex(0), parse.getArgumentVector());

		//char *cmd[] = {"cat", "myshell.cpp", NULL};
		//execvp(cmd[0], cmd);
	}
}


int main(int argc, char**argv){

	Parser parse;
	string input;
	bool inDebug = false;

	if(argv[1] != NULL && string(argv[1]) == "-Debug"){
		inDebug = true;
	}

	cout << "argv[0] " << argv[0] << endl;

			

	do { // while(input != "exit"){

		parse.runParser(inDebug);
		input = parse.getUserString();


		//char *cmd[] = {"ls", "-l", NULL};

		//execvp("ls", parse.getArgumentVector());
		//execvp("ls", cmd);

		runShell(parse, argv);

		parse.freeMem(); // free the memory allocated in runParser

	}while(input != "exit"); 

	

	return 0;
}
