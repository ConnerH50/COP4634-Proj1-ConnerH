#include "parse.hpp"
#include "errno.h"

void runShell(Parser parse, char** argv){
	int forkresult, returnstatus, inFile, outFile;
	//pid_t cpid;
	FILE *fp;
	
	forkresult = fork();

	if(forkresult != 0){ // parent runs this code, forkresult is childs pid
		if(parse.getBackground() == 0){
			//wait(NULL); // wait for child to finish
			waitpid(forkresult, &returnstatus, 0); // wait for child to finish
			cout << "The child is done" << endl;
		}else{
			cout << "\nParent " << getpid() << " is about to return, thus making a background process" << endl;
			return;
		}

	}else if(forkresult == -1){ // error in fork process
		
		cout << "Error in fork process" << endl;

	}else{ // child executes

		if(parse.getInputRedirect() != NULL){ // < sym, read from file
			
			inFile = open(parse.getInputRedirect(), O_RDONLY);

			if(dup2(inFile, STDIN_FILENO) == -1){
				cout << "Error dup2 failed" << endl;
			}

			close(inFile);
		}

		if(parse.getOutputRedirect() != NULL){ // > sym, write to file
			outFile = open(parse.getOutputRedirect(), O_WRONLY | O_CREAT);

			if(dup2(outFile, STDOUT_FILENO) == -1){
				cout << "Error, dup2 failed" << endl;
			}

			close(outFile);
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
