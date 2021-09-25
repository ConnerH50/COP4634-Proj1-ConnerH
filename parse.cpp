#include "parse.hpp"


Parser::Parser(){
	inputRedirect = NULL;
	outputRedirect = NULL;
	background = 0;
	argumentCount = 0;

}

void Parser::runParser(bool inDebug){
	userString = getUserInput();
	argumentVector = parseInput(userString);
	//cout << getArgumentCount() << endl;

	if(inDebug == true){
		printParams();
	}

}

void Parser::setArgumentCount(int argumentCount){
	this->argumentCount = argumentCount;
}

int Parser::getArgumentCount(){
	return argumentCount;
}

char *Parser::getUserInput(){
	cout << "$$$ ";
	char *line;
	size_t buffer = 0;
	getline(&line, &buffer, stdin);
	
	cout << line << endl;


	return line;
}

char *Parser::getUserString(){ // returns userString
	return userString;
}

char *Parser::getInputRedirect(){
	return inputRedirect;
}

char *Parser::getOutputRedirect(){
	return outputRedirect;
}

char **Parser::getArgumentVector(){
	return argumentVector;
}

char *Parser::getVectorIndex(int index){
	return argumentVector[index];
}

char **Parser::parseInput(char *userString){
	char **tokenArray;
	char *token;
	int size = MAXARGS;
	int argNum = 0;
	cout << "Inside parseInput" << endl;
	cout << userString << endl;

	tokenArray = (char**)malloc(size * sizeof(char*));
	
	token = strtok(userString, " \n");

	while(token != NULL){
		cout << token << endl;
		switch(token[0]){
			case '<':
				if(strcmp(token, "<") == 0){
					cout << "Error, inputRedirect cannot be empty" << endl;
					break;
				}else if(strcmp(token, "<\n") == 0){
					cout << "Error, inputRedirect cannot be empty" << endl;
					break;
				}
				memmove(token, token + 1, strlen(token)); // may need to change this to a substring	
				inputRedirect = token;
				break;
			case '>':
				if(strcmp(token, ">") == 0){
					cout << "Error, outputRedirect cannot be empty" << endl;
					break;

				}else if(strcmp(token, ">\n") == 0){
					cout << "Error, outputRedirect cannot be empty" << endl;
				}
				memmove(token, token + 1, strlen(token));
				outputRedirect = token;
				break;
			case '&':
				background = 1;
				break;
				
			default:
				tokenArray[argNum++] = token;
				break;
		}

		token = strtok(NULL, " \n"); //tokenizes on both whitespace and newline
	}
	
	tokenArray[argNum] = NULL;	
	setArgumentCount(argNum);
	return tokenArray;
}

void Parser::printParams(){
	if(inputRedirect == NULL){

	}else{
		cout << "InputRedirect :[" << inputRedirect << "]" << endl;
	}

	if(outputRedirect == NULL){

	}else{
		cout << "OutputRedirect :[" << outputRedirect << "]" << endl;
	}
	
	cout << "Argument Count: [" << argumentCount << "]" << endl;
	cout << "Background :[" << background << "]" << endl;


	for (int i = 0; i < argumentCount; i++){
		cout << "ArgumentVector[" << i << "]: [" << argumentVector[i]<< "]"<< endl;
	}

}

/*
 * Frees the memory allocated in getUserInput and ParseInput
 */
void Parser::freeMem(){
	inputRedirect = NULL;
	outputRedirect = NULL;

	free(argumentVector);
	free(userString);
}


