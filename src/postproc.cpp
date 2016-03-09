//
//  PostProc.cpp
//  OCR_cpp
//
//  Created by Terry Liao on 16/3/8.
//  Copyright © 2016年 Terry Liao. All rights reserved.
//

#include <iostream>
#include <string>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
#include "postproc.h"



//constructor
PostProc::PostProc(){
	Dict.resize(20);
	
	string dict[]={"auto","break","case","char","const",
		"continue","default","do","double","else",
		"enum","extern","float","for","goto",
		"if","int","long","register","return",
		"short","signed","sizeof","static","struct",
		"switch","typedef","union","unsigned","void",
		"volatile","while","program","include","Hello",
		"World","hello","world","printf","stdio",
		"main","scanf"};
	for(int i=0;i< 42;i++){
		Dict[dict[i].size()].push_back(dict[i]);
	}
}

//compare the word, return the fixed word
string PostProc::wordCompare(string word){
	int counter=0;
	int max=0;
	size_t len = word.size();
	char correction[len];
	for(int i=0; i<Dict[len].size();i++){
  counter=0;
		for(int j=0;j<len;j++){
			if (word[j]==Dict[len][i][j]){
				counter++;
			}
   
		}
		if (counter>max){
			max=counter;
			//	strcpy(correction,Dict[len][i]);
			Dict[len][i].copy(correction,Dict[len][i].size(),0);
			correction[len]='\0';
			
		}
		
	}
	if (len< 6 ) {
		if(max<len-2||max==0){
			//std::cout<<"word: "<<word << '\n';
			return word;
		}
		else{
			//std::cout<<"corrcet: "<<correction << '\n';
			return correction;
		}
		
	}else{
		if(max<len-3||max==0){
			//std::cout<<"word: "<< word<<'\n';
			return word;
		}
		else{
			//std::cout<<"correct: "<<correction << '\n';
			return correction;
		}
	}
	
	return word;
}
//add word to ditionary, optional
void PostProc::addword(string word){
	size_t len= word.size();
	Dict[len].push_back(word);
}

//fixed the symbols
string PostProc::symbolFix(){
	string removed;
	size_t start = 0, end = 0;
	string catchSymbol;
	size_t findCase,findDef, findSym;
	char near;
	int i;
	
	while (start+1 < fullText.length()) {
		
		start = fullText.find_first_of("/*|;:>#\"\'{}",end);
		if(start > fullText.length()){
			break;
		}
		end = start + 2;
		if (start == 0) {
			continue;
		}
		
		//fix ';' with ':'
		if (fullText[start] == ':') {
			findCase = fullText.rfind("case",start);
			if (findCase > fullText.size()) {
				findCase = 0;
				
			}
			findDef =  fullText.rfind("default",start);
			if (findDef > fullText.size()) {
				findDef = 0;
			}

			findSym = fullText.rfind(';',start);
			
			//cout<< findCase <<'\t'<<findDef<<'\t'<<findSym<<'\n';
			
			if(findCase > findSym || findDef > findSym){
				//unchange
			}else{
				fullText[start] = ';';
			}
			
		}
		
		
		
		//check symbols at the center of words, replace an alphabet letter
		i = 0;
		near = fullText[start-1];
		if ((near > 48 && near < 57) || (near > 65 && near < 90) || (near > 97 && near < 122)) {
			i++;
		}
		near = fullText[start+1];
		if ((near > 48 && near < 57) || (near > 65 && near < 90) || (near > 97 && near < 122)) {
			i++;
		}
		if (i >= 2) {
			fullText[start] = 'a';
		}
		
		
		
	}
	
	
	return fullText;
}
//fix the word with preset dictionary
string PostProc::dictFix(){
	std::size_t start = 0, end = 0;
	std::string word;
	while (end < fullText.length()) {
		start = fullText.find_first_not_of(" /*|.,;:+-#<>\"\'(){}\t\n",end);
		end = fullText.find_first_of(" /*|.,;:+-#<>\"\'(){}\t\n", start);
		
		if(start > fullText.length()||end > fullText.length()){
			break;
		}
		
		if (end-start > 0) {
			word = fullText.substr(start, end-start);
			fullText.replace(start, end-start,wordCompare(word));
		}
		
	}
	return fullText;
	
}

//public functions

//perform post processing
string PostProc::exicute(std::string str){
	fullText = str;
	fullText = symbolFix();
	fullText = dictFix();
	return fullText;
}






