#ifndef POSTPROC_H
#define POSTPROC_H

#include <string>
#include <vector>

class PostProc {
public:
	//Constructor
	PostProc(std::string input);
	
	//Destructor
	~PostProc();

	//Functions
	std::string execute();

private:
	//Constants
	static const std::string dictionary[];

	//Variables
	std::vector<std::vector<std::string>> words;
	std::string text;
	
	//Functions
	std::string fixSymbols();
	std::string fixWords();
	std::string compareWord(std::string word);
};

#endif	//POSTPROC_H
