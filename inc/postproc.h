//
//  PostProc.h
//  OCR_cpp
//
//  Created by Terry Liao on 16/3/8.
//  Copyright © 2016年 Terry Liao. All rights reserved.
//

#ifndef PostProc_h
#define PostProc_h

// string::substr
#include <iostream>
#include <string>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
using namespace std;

class PostProc{
private:
	std::vector<std::vector<std::string> > Dict;
	std::string fullText;//the full text pass in
	
	//private functions
	string symbolFix();	//fix symbols
	string dictFix();
	
public:
	//constructor
	PostProc();
	//destructor
	//~PostProc();
	//compare input word to dictionary and return the correct one
	string wordCompare(std::string word);
	//add word to dictionary
	void addword(std::string word);
	void getText(std::string str);
	string exportText();
	void exicute();
};

#endif /* PostProc_h */
