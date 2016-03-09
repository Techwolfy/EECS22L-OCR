//
//  main.cpp
//  OCR_cpp
//
//  Created by Terry Liao on 16/2/22.
//  Copyright © 2016年 Terry Liao. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <math.h>
#include "postproc.h"




int main ()
{
	std::ifstream ifs("post-test-in.txt");
	
	std::string str((std::istreambuf_iterator<char>(ifs)),
					std::istreambuf_iterator<char>());
	
	
	//size_t terminate = str.find('\0');
	
	string word;
	PostProc spellcheck;
	
	
	//std::cout << str <<'\n';
	
	str = spellcheck.exicute(str);
	
	//std::cout << str <<'\n';
	
	std::fstream file;
	file.open("post-test-out.txt", std::fstream::out | std::fstream::trunc);
	file << str;
	file.flush();
	file.close();
	
	std::cout <<"Post-processing test complete. CHECK OUTPUT FILE FOR RESULT!"<<'\n';
	
	
	
	return 0;
}