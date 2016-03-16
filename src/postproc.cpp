//PostProc.cpp

//Includes
#include <string>
#include <vector>
#include "postproc.h"

//Constants
const std::string PostProc::dictionary[] = {
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"function",
	"goto",
	"if",
	"int",
	"initial",
	"long",
	"main",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while",
	"program",
	"include",
	"Hello",
	"World",
	"hello",
	"world",
	"Helloworld",
	"printf",
	"program",
	"stdio",
	"main",
	"scanf",
	"EOF"};

//Constructor
PostProc::PostProc(std::string input) : text(input) {
	words.resize(sizeof(dictionary) / sizeof(std::string));
	for(int i = 0; i < sizeof(dictionary) / sizeof(std::string); i++) {
		words[dictionary[i].size()].push_back(dictionary[i]);
	}
}

//Destructor
PostProc::~PostProc() {
	
}

//Functions
//Fix symbols
std::string PostProc::fixSymbols() {
	int start = 0;
	int end = 0;
	int findCase = 0;
	int findDef = 0;
	int findSym = 0;
	char near = '\0';
	int i = 0;
	
	while(start + 1 < text.length()) {
		start = text.find_first_of("/*|;:>#\"\'{}", end);
		if(start > text.length()) {
			break;
		}
		end = start + 1;
		if(start == 0) {
			continue;
		}
		
		//fix ';' with ':'
		if(text[start] == ':' || text[start] == ';') {
			findCase = text.rfind("case", start);
			if(findCase > text.size()) {
				findCase = 0;
			}

			findDef = text.rfind("default", start);
			if(findDef > text.size()) {
				findDef = 0;
			}

			findSym = text.find_last_of(";", start);
			if(findCase > findSym || findDef > findSym) {
				text[start] = ':';
			} else {
				text[start] = ';';
			}
		}
		
		//Check symbols at the center of words, replace an alphabet letter
		i = 0;
		near = text[start - 1];
		if((near > 48 && near < 57) || (near > 65 && near < 90) || (near > 97 && near < 122)) {
			i++;
		}
		near = text[start + 1];
		if((near > 48 && near < 57) || (near > 65 && near < 90) || (near > 97 && near < 122)) {
			i++;
		}
		if(i >= 2) {
			text[start] = 'a';
		}
	}
	
	return text;
}

//Fix words with preset words
std::string PostProc::fixWords() {
	int start = 0;
	int end = 0;
	std::string word;

	while(end < text.length()) {
		start = text.find_first_not_of(" /*|.,;:+#<>\"\'(){}!\t\n", end);
		end = text.find_first_of(" /*|.,;:+#<>\"\'(){}!\t\n", start);
		
		if(start > text.length() || end > text.length()) {
			break;
		}
		
		if(end - start > 0) {
			word = text.substr(start, end - start);
			text.replace(start, end - start, compareWord(word));
		}
	}

	return text;
}

//Compare input word to words and return the correct one
std::string PostProc::compareWord(std::string word) {
	int counter = 0;
	int max = 0;
	int length = word.size();
	std::string correction;

	for(int i = 0; i < words[length].size(); i++) {
  		counter = 0;
		for(int j = 0; j < length; j++) {
			if(word[j] == words[length][i][j]) {
				counter++;
			}
		}
		if(counter > max) {
			max = counter;
			correction = words[length][i];
		}
	}
	if(length < 6) {
		if(max < length - 2 || max == 0) {
			return word;
		} else {
			return correction;
		}
	} else {
		if(max < length - 3 || max == 0) {
			return word;
		} else {
			return correction;
		}
	}

	return word;
}

//Perform post processing
std::string PostProc::execute() {
	fixSymbols();
	fixWords();
	return text;
}
