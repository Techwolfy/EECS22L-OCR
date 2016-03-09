//
//  main.cpp
//  OCR_cpp
//
//  Created by Terry Liao on 16/2/22.
//  Copyright © 2016年 Terry Liao. All rights reserved.
//


// string::substr
#include <iostream>
#include <string>
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
	std::string str= "/* He/lo World pro*ram */\n#include <stdio.h>\nvoid main(){\n	 chir test;	\n	c*ntlnuo;	\n	printf(\"Hello World\");\n}";
	

	
	//size_t terminate = str.find('\0');
	
	string word;
	PostProc spellcheck;
	
	
//	std::cout << str <<'\n';
	
	spellcheck.getText(str);
	
	spellcheck.exicute();
	
	str = spellcheck.exportText();
	
//	std::cout << str <<'\n';
	
	std::fstream file;
	file.open("postTest.txt", std::fstream::out | std::fstream::trunc);
	file << str;
	file.flush();
	file.close();
	
	
		
	
	return 0;
}