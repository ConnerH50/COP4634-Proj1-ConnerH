#include "parse.hpp"


Parser::Parser(){
	inputRedirect = NULL;
	outputRedirect = NULL;
	background = 0;
	argumentCount = 0;

}

void Parser::runParser(){
	userString = getUserInput();
	argumentVector = parseInput(userString);

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
	//char **tokens = malloc(size * sizeof(char*));
	token = strtok(userString, " ");

	while(token != NULL){
		tokenArray[argNum++] = token;
		//argumentVector[argNum++] = token;
		token = strtok(NULL, " ");
	}

	return tokenArray;
	//return tokens;
}

void Parser::freeMem(){
	free(argumentVector);
	free(userString);
}

Parser::~Parser(){
	//free(argumentVector);
	//free(tokens);
}
