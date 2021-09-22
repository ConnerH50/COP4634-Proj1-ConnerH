#include "parse.hpp"


Parser::Parser(){
	inputRedirect = NULL;
	outputRedirect = NULL;
	background = 0;
	argumentCount = 0;

}

void Parser::runParser(){
	userString = getUserInput();
	cout << userString << endl;

}

char *Parser::getUserInput(){
	cout << "$$$ ";
	char *line;
	
	char userInput[MAXARGS];

	size_t buffer = 0;
	int bufferSize = MAXARGS;
	getline(&line, &buffer, stdin);
	//fgets(userInput, bufferSize, stdin);

	//strcpy(line, userInput);

	cout << line << endl;


	return line;
}

char *Parser::getUserString(){ // returns userString
	return userString;
}

