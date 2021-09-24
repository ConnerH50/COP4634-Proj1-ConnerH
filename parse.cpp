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

char **Parser::parseInput(char *userString){
	char **tokenArray;
	char *token;
	int size = MAXARGS;
	int argNum = 0;
	cout << "Inside parseInput" << endl;
	cout << userString << endl;

	tokenArray = (char**)malloc(size * sizeof(char*));
	
	token = strtok(userString, " ");

	while(token != NULL){




		tokenArray[argNum++] = token;
		token = strtok(NULL, " ");
	}
	
	setArgumentCount(argNum);
	return tokenArray;
}

void Parser::printParams(){
	/*//cout << "InputRedirect :[" << inputRedirect << "]" << endl;
	//cout << "OutputRedirect :[" << outputRedirect << "]" << endl;
	//cout << "Argument Count: [" << argumentCount << "]" << endl;
	//cout << "Background :[" << background << "]" << endl;

	for(int i = 0; i < getArgumentCount(); i++){
		cout << "ArgumentVector[" << i << "]: [" <<
			argumentVector[i] << "]" << endl;
	}*/


	for (int i = 0; i < argumentCount; i++){
		cout << "ArgumentVector[" << i << "]: [" << argumentVector[i]<< "]"<< endl;
	}

}

/*
 * Frees the memory allocated in getUserInput and ParseInput
 */
void Parser::freeMem(){
	free(argumentVector);
	free(userString);
}


