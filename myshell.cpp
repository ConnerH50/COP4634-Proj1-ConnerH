#include "parse.hpp"
#include "errno.h"

void runShell(Parser parse, char** argv){
	int forkresult, returnStatus;
	pid_t cpid;
	FILE *fp;
	
	forkresult = fork();

	if(forkresult != 0){ // parent runs this code, forkresult is childs pid
		if(parse.getBackground() == 0){
			//wait(NULL); // wait for child to finish
			cpid = waitpid(forkresult, &returnStatus, 0); // wait for child to finish
			cout << "The child is done, with pid: " << forkresult << endl;
		}else{
			cout << "\nParent " << getpid() << " is about to return, thus making a background process, child pid is: " << forkresult << endl;
			return;
		}

	}else if(forkresult == -1){ // error in fork process
		
		cout << "Error in fork process" << endl;

	}else{ // child executes

		if(parse.getInputRedirect() != NULL){ // < sym, read from file
			
			if((fp = freopen(parse.getInputRedirect(), "r", stdin)) == NULL){
				cout << "File could not be opened" << endl;
			}

		}

		if(parse.getOutputRedirect() != NULL){ // > sym, write to file

			if((fp = freopen(parse.getOutputRedirect(), "w+", stdout)) == NULL){
				cout << "File could not be opened" << endl;
			}
		}

		
		execvp(parse.getVectorIndex(0), parse.getArgumentVector());
	}
}


int main(int argc, char**argv){

	Parser parse;
	string input;
	bool inDebug = false;

	if(argv[1] != NULL && string(argv[1]) == "-Debug"){
		inDebug = true;
	}

			

	while(input != "exit"){

		parse.runParser(inDebug);
		input = parse.getUserString();

		if(input == "exit"){ 
			//cout << "input is exit" << endl;
			parse.freeMem();
			wait(NULL); // wait for child processes to finish
			//return 0;
		}else{

			runShell(parse, argv);
			parse.freeMem(); // free the memory allocated in runParser
		}

	} 

	

	return 0;
}
