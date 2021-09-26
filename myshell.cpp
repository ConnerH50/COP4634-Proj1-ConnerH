#include "parse.hpp"

void runShell(Parser parse, char** argv){
	int forkresult, returnstatus;
	pid_t cpid;
	
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

	}else  if(forkresult == -1){ // error in fork process
		
		cout << "Error in fork process" << endl;

	}else{ // child executes

		
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
