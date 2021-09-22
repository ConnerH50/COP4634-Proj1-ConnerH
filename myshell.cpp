#include "parse.hpp"


int main(int argc, char**argv){

	Parser parse;

	do{
		parse.runParser();
	} while(strcmp(parse.getUserString(), "exit\n") != 0); // dont forget the newline character on exit

	cout << strcmp(parse.getUserString(), "exit\n") << endl;
	cout << parse.getUserString() << endl;

	return 0;
}
