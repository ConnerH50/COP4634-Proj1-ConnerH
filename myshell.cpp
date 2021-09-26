#include "parse.hpp"
#include "errno.h"

int backgroundProcesses = 0;

void runShell(Parser parse, char** argv){
	int forkresult, returnStatus;
	//pid_t cpid;
	FILE *fp;
	
	forkresult = fork();

	if(forkresult != 0){ // parent runs this code, forkresult is childs pid
		if(parse.getBackground() == 0){
			waitpid(forkresult, &returnStatus, 0); // wait for child to finish
			cout << "The child is done, with pid: " << forkresult << endl;
		}else{
			cout << "\nParent " << getpid() << " is about to return, thus making a background process, child pid is: " << forkresult << endl;
			backgroundProcesses++;
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
	int resultStatus;
	pid_t pid;


	if(argv[1] != NULL && string(argv[1]) == "-Debug"){
		inDebug = true;
	}

			

	while(input != "exit"){

		parse.runParser(inDebug);
		input = parse.getUserString();

		if(input == "exit"){ // at exit immedietly free any allocated memory and wait
			parse.freeMem();

			while((pid = waitpid(-1, &resultStatus, 0)) != -1){
				cout << "Waiting on background process to finish" << endl;
			}

			//wait(NULL); // wait forany child processes to finish
		}else{

			runShell(parse, argv);
			parse.freeMem(); // free the memory allocated in runParser
		}

	} 
	return 0;
}
