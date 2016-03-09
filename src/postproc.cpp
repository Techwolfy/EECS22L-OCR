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



PostProc::PostProc(){
	Dict.resize(20);
	
	string dict[]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","program","include","Hello","World","hello","world"};
	for(int i=0;i<38;i++){
		Dict[dict[i].size()].push_back(dict[i]);
	}
}


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

void PostProc::addword(string word){
	size_t len= word.size();
	Dict[len].push_back(word);
}


string PostProc::symbolFix(){
	string removed;
	size_t start = 0, end = 0;
	string catchSymbol;
	char near;
	int i;
	
	while (end < fullText.length()) {
		i = 0;
		start = fullText.find_first_of("/*;<>#\"\'{}",end);
		end = start +2;
		if (start >1 && start < fullText.length()) {
			catchSymbol = fullText.substr(start-1,3);
			
		}else if(start > fullText.length()){
			break;
		}
		else{
			continue;
		}
		
		near = catchSymbol[0];
		if ((near > 48 && near < 57) || (near > 65 && near < 90) || (near > 97 && near < 122)) {
			i++;
		}
		near = catchSymbol[2];
		if ((near > 48 && near < 57) || (near > 65 && near < 90) || (near > 97 && near < 122)) {
			i++;
		}
		if (i >= 2) {
			fullText.replace(start, 1, "a");
		}
		
		
	}
	
	
	return fullText;
}

string PostProc::dictFix(){
	std::size_t start = 0, end = 0;
	std::string word;
	while (end < fullText.length()) {
		start = fullText.find_first_not_of(" \n/*;#<>\"\'(){}\t.",end);
		end = fullText.find_first_of(" \n/*;#<>\"\'(){}.\t", start);
		
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


void PostProc::exicute(){
	fullText = symbolFix();
	fullText = dictFix();
}

void PostProc::getText(std::string str){
	fullText = str;
}

string PostProc::exportText(){
	return fullText;
}




