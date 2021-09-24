#include "parse.hpp"


int main(int argc, char**argv){

	Parser parse;
	string input;

	do{
		parse.runParser();
		input = parse.getUserString();
		parse.freeMem();

	} while(input != "exit\n"); 

	

	return 0;
}
