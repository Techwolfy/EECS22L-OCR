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
	//the vecter to store the ditionary
	std::vector<std::vector<std::string> > Dict;
	//the full text pass in
	std::string fullText;
	
	//private functions
	//fix symbols
	string symbolFix();
	//fix words
	string dictFix();
	//compare input word to dictionary and return the correct one
	string wordCompare(std::string word);
	
public:
	//constructor
	PostProc();
	//destructor
	~PostProc();
	//add word to dictionary
	void addword(std::string word);
	//to do all the process and ouputing the text
	string exicute(std::string str);
};

#endif /* PostProc_h */
