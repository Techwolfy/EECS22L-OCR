/*********************************************************************/ 
/* Image.hpp: header file for image class                    		     */ 
/*                                                                   */
/*********************************************************************/ 
#ifndef IMAGE_HPP
#define IMAGE_HPP
#define SLEN    80		/* maximum length of file names */
#include <string>
#include <iostream>
#include <vector>
using std::vector;

	class IMAGE{
	public:
	int WIDTH;
	int HEIGHT;
	vector<vector<unsigned char> > R;
	vector<vector<unsigned char> > G;
	vector<vector<unsigned char> > B;
 
	public:

	IMAGE();
	IMAGE(int w, int r);//construction declaration
	~IMAGE();//destructor declaration
	
	int SaveImage(const char fname[SLEN]);
  void BlackNWhite();	

	};

#endif
